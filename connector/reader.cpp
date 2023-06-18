#include "reader.hpp"

CTF::Connector::reader::reader(boost::asio::io_context& context, unsigned short port, std::function<void(std::string)> callback)
: socket_(context), resolver_(context), 
acceptor_(context, tcp::endpoint(tcp::v4(), port)),
callback_(callback) { }

void CTF::Connector::reader::receive() {
    acceptor_.accept(socket_);
    try
    {
        std::string buffer;
        boost::asio::read_until(socket_, 
            boost::asio::dynamic_buffer(buffer), "\0");
        callback_(buffer);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
