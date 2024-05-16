#include "proxy.hpp"
#include <chrono>




Proxy::Proxy(boost::asio::io_context& io, std::string const& host, unsigned short port) : _io{ io }, _host{ host }, _port { port }
{
	
}

void Proxy::start()
{
	boost::asio::co_spawn(_io, this->listen(), boost::asio::detached);
}

boost::asio::awaitable<void> Proxy::listen()
{
	auto acceptor = boost::asio::ip::tcp::acceptor(_io, { boost::asio::ip::tcp::v4(), _port });
	for (;;) {
		auto socket = co_await acceptor.async_accept(boost::asio::use_awaitable);
		boost::asio::co_spawn(_io, this->session(std::move(boost::beast::tcp_stream(std::move(socket)))), boost::asio::detached);
	}
}

boost::asio::awaitable<void> Proxy::session(boost::beast::tcp_stream client_stream)
{
	using namespace std::chrono_literals;

	for (;;) {
		client_stream.expires_after(10s);
		boost::beast::http::request<boost::beast::http::string_body> request;
		boost::beast::flat_buffer buffer;
		// reading client request
		co_await boost::beast::http::async_read(client_stream, buffer, request, boost::asio::use_awaitable);
		print("Request: " + request_to_string(request));
		
		auto ctx = setup_ssl_context();
		boost::beast::ssl_stream<boost::beast::tcp_stream> ssl_server_stream(_io, ctx);
		auto resolver = boost::asio::ip::tcp::resolver(_io);
		boost::beast::http::response<boost::beast::http::dynamic_body> response;	

		auto results = co_await resolver.async_resolve(_host, "443", boost::asio::use_awaitable);
		boost::beast::get_lowest_layer(ssl_server_stream).expires_after(30s);
		co_await boost::beast::get_lowest_layer(ssl_server_stream).async_connect(results, boost::asio::use_awaitable);
		boost::beast::get_lowest_layer(ssl_server_stream).expires_after(30s);
		co_await ssl_server_stream.async_handshake(boost::asio::ssl::stream_base::client, boost::asio::use_awaitable);
		
		print("Connected to: " + _host);
		// creating a request

		boost::beast::http::request<boost::beast::http::string_body> req(boost::beast::http::verb::get, "/", 11);
		req.set(boost::beast::http::field::host, _host);
		req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
		
		co_await boost::beast::http::async_write(ssl_server_stream, req, boost::asio::use_awaitable);
		co_await boost::beast::http::async_read(ssl_server_stream, buffer, response, boost::asio::use_awaitable);
		print("Response: " + response_to_string(response));

		co_await boost::beast::http::async_write(client_stream, response, boost::asio::use_awaitable);
	}
}

void print(std::string const& message) noexcept
{
#if HAS_STD_PRINT
	std::println("{}", message);
#else 
	std::cout << message << std::endl;
#endif
}

std::string request_to_string(boost::beast::http::request<boost::beast::http::string_body>const& req)
{
	std::string req_str = req.method_string();
	req_str += " ";
	req_str += req.target();
	req_str += " HTTP/" + std::to_string(req.version()/ 10) + "." + std::to_string(req.version() % 10) + "\r\n";

	// add headers
	for(auto const& field: req.base())
		req_str += std::string(field.name_string()) + ": " + std::string(field.value()) + "\r\n";

	req_str += "\r\n";

	// Add body if present
	if (req.body().size() > 0) {
		req_str += req.body();
	}

	return req_str;
}

std::string response_to_string(boost::beast::http::response<boost::beast::http::dynamic_body> const& res)
{
	std::string res_str = "HTTP/";
	res_str += std::to_string(res.version() / 10) + ".";
	res_str += std::to_string(res.version() % 10) + " ";
	res_str += std::to_string(res.result_int()) + " ";
	res_str += std::string(res.reason()) + "\r\n";

	for (auto const& field : res.base()) {
		res_str += std::string(field.name_string()) + ": " +
			std::string(field.value()) + "\r\n";
	}
	res_str += "\r\n";
	res_str += boost::beast::buffers_to_string(res.body().data());
	return res_str;
}

boost::asio::ssl::context setup_ssl_context()
{
	boost::asio::ssl::context ctx(boost::asio::ssl::context::tlsv12_client);
	ctx.set_default_verify_paths();
	return ctx;
}
