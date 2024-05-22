//
// Created by mahdi on 5/22/24.
//

#ifndef FILESHARINGSERVER_H
#define FILESHARINGSERVER_H

#include <boost/asio.hpp>
#include <fstream>


class FileSharingServer {
public:
    FileSharingServer(boost::asio::io_context &io, unsigned short const port);
    void start();
    boost::asio::awaitable<void> listen();
    boost::asio::awaitable<void> read_file(boost::asio::ip::tcp::socket socket);
    boost::asio::awaitable<void> process_on_file(boost::asio::ip::tcp::socket socket);
private:
    boost::asio::io_context &_io;
    boost::asio::ip::tcp::acceptor _acceptor;
    std::array<char, 1024> _data{};
    long unsigned int _read_lengh{};
    inline static int file_counter{1};
};



#endif //FILESHARINGSERVER_H
