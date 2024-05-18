#ifndef ConnectingSocket_hpp
#define ConnectingSocket_hpp

#include "SimpleSocket.hpp"

namespace RIK {
    class ConnectingSocket : public SimpleSocket {
        public:
            ConnectingSocket(int domain, int type, int protocol, int port, u_long interface);
      
            int connectToNetwork(int sock, sockaddr_in address) override;
        private:
    };

}

#endif