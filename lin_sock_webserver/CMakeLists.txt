
set(SOURCES 

        Networking/Sockets/SimpleSocket.hpp
        Networking/Sockets/SimpleSocket.cpp
        Networking/Sockets/BindingSocket.cpp 
        Networking/Sockets/BindingSocket.hpp
        Networking/Sockets/ConnectingSocket.cpp 
        Networking/Sockets/ConnectingSocket.hpp
        Networking/Sockets/ListeningSocket.cpp 
        Networking/Sockets/ListeningSocket.hpp
        Networking/Servers/SimpleServer.hpp
        Networking/Servers/SimpleServer.cpp
        Networking/Servers/RikServer.cpp
        Networking/Servers/RikServer.hpp
        riklibc.hpp riklibc.cpp
        )
add_executable(linux_webserver ${SOURCES})