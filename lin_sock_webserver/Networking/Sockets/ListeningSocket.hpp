#ifndef ListeningSocket_hpp
#define ListeningSocket_hpp

#include "BindingSocket.hpp"

namespace RIK {
    class ListeningSocket : public BindingSocket{
        public:
            ListeningSocket(int domain, 
            int type, int protocol, int port, u_long interface, int backlog);

        void startListening() noexcept;
        int getListening() noexcept;
        int getBackLog() noexcept;
        
        private:
        int _backlog;
        int _listening;
    };
}
#endif 