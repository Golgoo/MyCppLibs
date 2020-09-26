#pragma once

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>

#include <string>
#include <stdexcept>

#include <thread>
#include <iostream>

#include <my/concurrent/blocking_safe_queue.hpp>
#include <map>

namespace my{
namespace network{

struct identifier{
    std::string addr ;
    uint16_t port ;

    bool operator<(const identifier &other) const {
        if(port < other.port ) return true;
        else if(addr < other.addr) return true;
        return false;
    }
};

struct mess_src{
    identifier identity ;
    std::string content ;
};


class Server
{
    private:
        int _port ;
        std::string _address ;
        int _maximum_connection ;
        int _buffer_size = 1024 ;
        my::concurrent::BlockingSafeQueue<mess_src> _queue ;
        std::map<identifier, int> _address_to_socket_map ;
    private:
        int _server_fd = -1 ;
    public:
        Server(std::string address, int port, int maximum_connection = 5);
        ~Server();
    private:
        void createServerSocket();
        void infiniteLoop();
        void starting_connection(int client_socket_id, identifier clientIdentity);
        std::string readLine(int client_socket_id, std::string & buffer);
    public:
        int send_message_to(const identifier &identity, std::string message);
        void startListening(const bool blocking);
        mess_src popMessage(){
            return _queue.pop_first();
        };
        void extendWhiteList(identifier identity){
            if(_address_to_socket_map.count(identity) == 0){
                _address_to_socket_map[identity] = -1 ;
            }
        }
};

}
}