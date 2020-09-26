#include <my/network/server.hpp>


using namespace my::network;

Server::Server(std::string address, int port, int maximum_connection):
_address(address),
_port(port),
_maximum_connection(maximum_connection),
_address_to_socket_map()
{
   createServerSocket();
}

Server::~Server()
{
    close(_server_fd);
}

void Server::createServerSocket()
{
    int opt = 1 ;
    struct sockaddr_in address;

    _server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(_server_fd < 0){
        throw std::runtime_error("Unable to create socket file descriptor");
    }
    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0) 
    {
        throw std::runtime_error("Unable to attach server socket");
    }
    address.sin_family = AF_INET; 
    inet_aton(_address.c_str(), &address.sin_addr); 
    address.sin_port = htons( _port );
       
    if (bind(_server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    {
        throw std::runtime_error("Unable to bind the server socket to the given address and port : ");
    }
}

void Server::startListening(const bool blocking)
{
    if (listen(_server_fd, _maximum_connection) < 0) 
    {
        throw std::runtime_error("Unable to listen");
    }
    if(blocking){
        infiniteLoop();
    }else{
        std::thread infinite_loop_thread(&Server::infiniteLoop, this);
        infinite_loop_thread.detach();
    }
}

void Server::infiniteLoop()
{
    int client_socket_id ;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    while(true){
        if ((client_socket_id = accept(_server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
        {
            std::clog << "Unable to accept the connection " << std::endl;
        }else{
            identifier clientIdentity ;
            clientIdentity.port = ntohs (address.sin_port) ;
            clientIdentity.addr = inet_ntoa(address.sin_addr);
            if(_address_to_socket_map.count(clientIdentity) > 0){
                _address_to_socket_map[clientIdentity] = client_socket_id ;
                std::thread starting_connection_thread(
                    &Server::starting_connection, this, 
                    client_socket_id, 
                    clientIdentity
                );
                starting_connection_thread.detach();
            }else{
                close(client_socket_id);
            }
        }
    }
}

std::string Server::readLine(int client_socket_id, std::string & buffer)
{
    int index ;
    do{
        index = buffer.find_first_of('\n');
        if(index < 0){
            char tmp_buffer[1024] = {"\0"};
            if(read(client_socket_id, tmp_buffer, _buffer_size) <= 0){
                return "";
            }
            buffer.append(tmp_buffer) ;
        }
    }while(index < 0);
    std::string tmp_str = buffer.substr(0, index);
    buffer.erase(0, index + 1);
    return tmp_str;
}

void Server::starting_connection(int client_socket_id, identifier clientIdentity)
{
    mess_src msg ;
    msg.identity = clientIdentity ;

    std::string buffer = {""};
    std::string line = readLine(client_socket_id, buffer);

    while(! line.empty()){
        msg.content = line ;
        _queue.push_back(msg);
        line = readLine(client_socket_id, buffer);
    }
    close(_address_to_socket_map[clientIdentity]);
    _address_to_socket_map[clientIdentity] = -1 ;
}

int Server::send_message_to(const identifier &identity, std::string message)
{
    return send(_address_to_socket_map[identity], message.c_str(), message.size(), 0 );
}

