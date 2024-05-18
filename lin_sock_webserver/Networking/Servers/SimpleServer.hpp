#ifndef SimpleServer_hpp
#define SimpleServer_hpp

#include "../Sockets/ListeningSocket.hpp"
#include <memory>

namespace RIK {
    class SimpleServer {
        public:
            SimpleServer(int domain, int type, int protocol, int port, u_long interface, int backlog);
            std::shared_ptr<ListeningSocket> get_socket() noexcept;

            virtual void reciver() = 0;
            virtual void acceptor() = 0;
            virtual void answer() = 0;
            virtual void lunch() = 0;
        private:
            std::shared_ptr<ListeningSocket> _socket;

    };
}

#endif