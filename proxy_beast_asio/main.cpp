#include "Proxy.hpp"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::println("Usage: ./proxy <host> <port> ");
        return -1;
    }
    try {
        boost::asio::io_context io;
        Proxy proxy(io, argv[1], std::stoi(argv[2]));
        
        // capture termination requests
        boost::asio::signal_set signals(io, SIGINT, SIGTERM);
        signals.async_wait([&](boost::system::error_code const& error, int sig_number) {
            if (!error) {
                std::println("Bye Bye!");
                io.stop();
            }
                
            });

        proxy.start();
        io.run();
    }
    catch (std::exception const& error) {
        using namespace std::string_literals;
        print("Error: "s + error.what());
    }
    return 0;
}