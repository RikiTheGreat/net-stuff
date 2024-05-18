#include "ConnectingSocket.hpp"

RIK::ConnectingSocket::ConnectingSocket(int domain,
                                        int type,
                                        int protocol, 
                                        int port, 
                                        u_long interface):
                            SimpleSocket(domain, type, protocol, port, interface){
    
    setConnection(connectToNetwork(getSocket(), getAddress()));
    testConnection(getConnection());
 }


int RIK::ConnectingSocket::connectToNetwork(int sock, sockaddr_in address)
{
    return connect(sock, (sockaddr*) &address, sizeof(address));
}
  