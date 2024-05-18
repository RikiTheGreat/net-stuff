#ifndef RikServer_hpp
#define RikServer_hpp

#include "SimpleServer.hpp"

namespace RIK {
    class RikServer : public SimpleServer {
        public:
            RikServer(int domain, int type, int protocol, int port, u_long interface, int backlog);

            void reciver() override;
            void acceptor() override;
            void answer() override;
            void lunch() override;
        private:
            int _new_socket;
            char _buffer[3000] {};
    };
}

#endif 