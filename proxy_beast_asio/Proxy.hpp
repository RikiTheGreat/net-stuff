#pragma once
#include <version>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/ssl.hpp>
#include <string>

#ifdef __has_include
#   if __has_include(<print>)
#include <print>
#define HAS_STD_PRINT 1
#   else
#include <iostream>
#define HAS_STD_PRINT 0
#   endif
#endif

void print(std::string const& message) noexcept;

class Proxy {
public:
    Proxy(boost::asio::io_context& io, std::string const& host, unsigned short port);
    void start();
    boost::asio::awaitable<void> listen();
    boost::asio::awaitable<void> session(boost::beast::tcp_stream client_stream);
private:
    boost::asio::io_context& _io;
    unsigned short _port{};
    std::string _host;
};

std::string request_to_string(boost::beast::http::request<boost::beast::http::string_body> const& req);
std::string response_to_string(boost::beast::http::response<boost::beast::http::dynamic_body> const& res);
boost::asio::ssl::context setup_ssl_context();