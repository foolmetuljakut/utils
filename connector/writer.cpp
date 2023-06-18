#include "writer.hpp"

CTF::Connector::writer::writer(boost::asio::io_context& context, std::string targetaddress, std::string targetport)
: io_context_(context), socket_(io_context_), resolver_(io_context_) {
    endpoints_ = resolver_.resolve(targetaddress, targetport);
    // boost::asio::connect(socket_, endpoints);
}

void CTF::Connector::writer::connect() {
    boost::asio::connect(socket_, endpoints_);
}

void CTF::Connector::writer::write(std::string msg) {
    boost::asio::write(socket_, 
        boost::asio::buffer(msg + "\0"));
}

void CTF::Connector::writer::disconnect() {
    socket_.close();
}

