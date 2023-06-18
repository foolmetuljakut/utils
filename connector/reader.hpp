#ifndef ctf_connector_reader
#define ctf_connector_reader

#include <iostream>
#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <functional>

using boost::asio::ip::tcp;

namespace CTF::Connector {

    class reader {
    public:
        static std::unique_ptr<reader> create(boost::asio::io_context& context, unsigned short port, std::function<void(std::string)> callback) {
            return std::unique_ptr<reader>(new reader(context, port, callback));
        }
        void receive();
    private:
        reader(boost::asio::io_context& context, unsigned short port, std::function<void(std::string)> callback);
        boost::asio::io_context io_context_;
        boost::asio::ip::tcp::socket socket_;
        boost::asio::ip::tcp::resolver resolver_;
        tcp::acceptor acceptor_;
        std::function<void(std::string)> callback_;
    };

};

#endif // !ctf_connector_reader