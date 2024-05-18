#include "SimpleSocket.hpp"
#include <memory.h>

RIK::SimpleSocket::SimpleSocket(int domain,
                                int type,
                                int protocol,
                                int port, 
                                u_long interface) {

    _socket = socket(domain, type, protocol);
    testConnection(_socket);
    _address.sin_family = domain;
    _address.sin_port = htons(port);
    _address.sin_addr.s_addr = htonl(interface);
    memset(&_address.sin_zero, 0, sizeof(_address.sin_zero));
    
}

int RIK::SimpleSocket::getSocket() const noexcept {
    return this->_socket;
}

void RIK::SimpleSocket::testConnection(int item) noexcept
{
    if(item < 0) {
        std::cerr << "Faild to connect ..." << std::endl;
        exit(EXIT_FAILURE);
    }
}

sockaddr_in RIK::SimpleSocket::getAddress() noexcept
{
    return this->_address;
}

int RIK::SimpleSocket::getConnection() noexcept
{
    return this->_connection;
}

void RIK::SimpleSocket::setConnection(int con) noexcept
{
    this->_connection = con;
}
