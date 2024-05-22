
#include <iostream>
#include "FileSharingServer.h"

int main(int argc, char** argv)  {
    boost::asio::io_context io;
    FileSharingServer srv(io, 4444);
    srv.start();
    io.run();
}
