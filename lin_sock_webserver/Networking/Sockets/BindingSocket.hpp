#ifndef BindingSocket_hpp
#define BindingSocket_hpp
#include "SimpleSocket.hpp"

namespace RIK {
    class BindingSocket : public SimpleSocket {
        public:
            BindingSocket(int domain, int type, int protocol, int port, u_long interface);
    
            int connectToNetwork(int sock, struct sockaddr_in address) override;
    };
}
#endif