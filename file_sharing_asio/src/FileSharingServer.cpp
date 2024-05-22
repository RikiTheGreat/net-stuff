#include "FileSharingServer.h"
#include <iostream>
#include <array>
#include <print>
#include "logger.h"

FileSharingServer::FileSharingServer(boost::asio::io_context &io, unsigned short const port): _io{io},
    _acceptor{io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)} {}

void FileSharingServer::start() {
    boost::asio::co_spawn(_io, this->listen(), boost::asio::detached);
}

boost::asio::awaitable<void> FileSharingServer::listen() {
    for(;;) {
        auto socket = co_await _acceptor.async_accept(boost::asio::use_awaitable);
        boost::asio::co_spawn(_io, this->read_file(std::move(socket)), boost::asio::detached);
    }
}

boost::asio::awaitable<void> FileSharingServer::read_file(boost::asio::ip::tcp::socket socket) {
    try {
        _read_lengh = co_await socket.async_read_some(boost::asio::buffer(_data), boost::asio::use_awaitable);
        boost::asio::co_spawn(_io, this->process_on_file(std::move(socket)), boost::asio::detached);
    }catch(std::exception const& e) {
        log(e.what());
    }
}

boost::asio::awaitable<void> FileSharingServer::process_on_file(boost::asio::ip::tcp::socket socket) {
    try {
        std::ofstream outputFile("recved_file" + std::to_string(file_counter), std::ios_base::binary);
        if(!outputFile.is_open()) {
            log("Error: cannot open outputFile!");
        }

        outputFile.write(_data.data(), _read_lengh);
        file_counter++;
        co_await boost::asio::async_write(socket, boost::asio::buffer("catcha"), boost::asio::use_awaitable);
        socket.shutdown(boost::asio::socket_base::shutdown_both);
        socket.close();
    }catch(std::exception const& e) {
        log(e.what());
    }
}
