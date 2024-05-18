#include "BindingSocket.hpp"

RIK::BindingSocket::BindingSocket(int domain, 
                                  int type, 
                                  int protocol, 
                                  int port, 
                                  u_long interface) : 
                                  SimpleSocket(domain, type, protocol,
                                               port, interface){

    setConnection(connectToNetwork(getSocket(), getAddress()));
    testConnection(getConnection());
}

int RIK::BindingSocket::connectToNetwork(int sock, sockaddr_in address)
{
    return bind(sock, (sockaddr*)&address, sizeof(address));
}
