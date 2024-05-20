#include "RikServer.hpp"
#include <string.h>

RIK::RikServer::RikServer(int domain, 
                        int type, 
                        int protocol,
                        int port,
                        u_long interface, 
                        int backlog) : SimpleServer(domain,
                                                type,
                                                protocol, 
                                                port, 
                                                interface, 
                                                backlog){


}

void RIK::RikServer::reciver()
{
    std::cout << _buffer << std::endl;
}

void RIK::RikServer::acceptor()
{
    sockaddr_in address = get_socket()->getAddress();
    int addrlen = sizeof(address);
    _new_socket = accept(get_socket()->getSocket(), (sockaddr*)&address, (socklen_t*)&addrlen);
    int n = read(_new_socket, _buffer, 3000);
    get_socket()->testConnection(n);
}

void RIK::RikServer::answer()
{
    char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                      "<html>\n"
                      "<head><title>My Web Server</title></head>\n"
                      "<body>\n"
                      "<h1>Welcome to my Web Server!</h1>\n"
                      "</body>\n"
                      "</html>\n";

    int n = write(_new_socket, response, strlen(response));
    get_socket()->testConnection(n);
    close(_new_socket);
}

void RIK::RikServer::lunch()
{
    for(;;) {
        acceptor();
        reciver();
        answer();
    }
}
