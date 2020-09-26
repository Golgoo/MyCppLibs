#include <my/network/client.hpp>

using namespace my::network ;

Client::Client(std::string server_address, ushort server_port, std::string client_address, ushort client_port):
_server_address(server_address),
_server_port(server_port),
_client_address(client_address),
_client_port(client_port)
{
    createASocket();
    connectASocketToTheServer();
}

Client::Client(ClientConstructionInfo& clientConstructionInfo):
_server_address(clientConstructionInfo.server_address),
_server_port(clientConstructionInfo.server_port),
_client_address(clientConstructionInfo.client_address),
_client_port(clientConstructionInfo.client_port)
{
    createASocket();
    connectASocketToTheServer();
}

void Client::createASocket()
{
    if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        throw std::runtime_error("Unable to create the socket");
    }
    int opt = 1 ;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0) 
    {
        throw std::runtime_error("Unable to attach client socket");
    }
    struct sockaddr_in address;
    address.sin_family = AF_INET; 
    inet_aton(_client_address.c_str(), &address.sin_addr); 
    address.sin_port = htons( _client_port );
       
    if (bind(_socket, (struct sockaddr *)&address, sizeof(address))<0) 
    {
        throw std::runtime_error("Unable to bind the client socket to the given address and port : ");
    }
}

void Client::connectASocketToTheServer()
{
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(_server_port);
    if(inet_pton(AF_INET, _server_address.c_str(), &serv_addr.sin_addr)<=0)  
    { 
        throw std::runtime_error("The adress is incorrect");
    }
    if (connect(_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        throw std::runtime_error("Unable to connect to the server");
    }
}

int Client::sendMessage(std::string message)
{
    message.append("\n");
    return send(_socket, message.c_str(), message.size(), 0 );
}

std::string Client::readMessage()
{
    char tmp_buffer[1024] = {"\0"};
    if(read(_socket, tmp_buffer, 1024) <= 0){
        return "";
    }
    return tmp_buffer ;
}