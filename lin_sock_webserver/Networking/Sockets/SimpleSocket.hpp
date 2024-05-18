#ifndef SimpleSocket_hpp
#define SimpleSocket_hpp

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>


namespace RIK {
    class SimpleSocket {
        public:
            SimpleSocket(int domain, int type, int protocol, int port, u_long interface);

            virtual int connectToNetwork(int sock, struct sockaddr_in address) = 0;
             int getSocket() const noexcept;
             void testConnection(int item) noexcept;
             sockaddr_in getAddress() noexcept;
             int getConnection() noexcept;
             void setConnection(int con) noexcept;
        private:
            int _socket;
            sockaddr_in _address;
            int _connection;
    };
}
#endif

