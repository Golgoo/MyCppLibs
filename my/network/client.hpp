#pragma once

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <netinet/tcp.h>

#include <string>
#include <stdexcept>

namespace my{
namespace network{

    struct ClientConstructionInfo{
        ushort server_port ;
        ushort client_port ;
        std::string server_address ;
        std::string client_address ;
    };

    
    class Client
    {
        private :
            int _socket = -1 ;
            std::string _server_address ;
            ushort _server_port ;

            std::string _client_address ;
            ushort _client_port ;
        
        public:
            Client(std::string server_address, ushort server_port, std::string client_address, ushort client_port);
            Client(ClientConstructionInfo& clientConstructionInfo);
            ~Client(){
                close(_socket);
            }

        private:
            void createASocket();
            void connectASocketToTheServer();

        public:
            int sendMessage(std::string message);
            std::string readMessage();
    };


}
}