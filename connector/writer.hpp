#ifndef ctf_connector_writer_hpp
#define ctf_connector_writer_hpp

#include <iostream>
#include <deque>
#include <string>
#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace CTF::Connector {

    class writer {
    public:
        static std::unique_ptr<writer> create(boost::asio::io_context& context, std::string targetaddress, std::string targetport) {
            return std::unique_ptr<writer>(new writer(context, targetaddress, targetport));
        }
        void connect();
        void write(std::string msg);
        void disconnect();
    private:
        writer(boost::asio::io_context& context, std::string targetaddress, std::string targetport);
        boost::asio::io_context& io_context_;
        tcp::socket socket_;
        tcp::resolver resolver_;
        boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> endpoints_;
    };
    
};

#endif