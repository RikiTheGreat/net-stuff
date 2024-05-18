#include "ListeningSocket.hpp"

RIK::ListeningSocket::ListeningSocket(int domain, 
int type, int protocol, int port,  u_long interface, int backlog)
    : BindingSocket(domain, type, protocol, port, interface), _backlog(backlog){
        startListening();
        testConnection(_listening);
    }

void RIK::ListeningSocket::startListening() noexcept
{
    this->_listening = listen(getSocket(), this->_backlog);
}

int RIK::ListeningSocket::getListening() noexcept
{
    return _listening;
}

int RIK::ListeningSocket::getBackLog() noexcept
{
    return _backlog;
}
