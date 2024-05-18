#include "SimpleServer.hpp"

RIK::SimpleServer::SimpleServer(int domain, int type, int protocol, int port, u_long interface, int backlog)
{
    _socket.reset(new ListeningSocket(domain, type, protocol, port, interface, backlog));
}

std::shared_ptr<RIK::ListeningSocket> RIK::SimpleServer::get_socket() noexcept
{
    return this->_socket;
}
