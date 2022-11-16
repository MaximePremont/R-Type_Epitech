//
// Created by mikael-vallenet on 01/11/22.
//

#include "TCPClient.hpp"

Library::TCPClient::TCPClient(boost::asio::io_context& io_context, std::string address, std::string port) : _socket(io_context),
                                                                                      _resolver(io_context) {
        boost::asio::connect(_socket, _resolver.resolve(address, port));
}

void Library::TCPClient::getServer() {
        std::string str_buff("GET server\n");
        std::string str_recv(max_length, '\0');
         boost::asio::streambuf recv_buffer;

        boost::asio::write(_socket, boost::asio::buffer(str_buff, str_buff.length()));
        boost::asio::read_until(_socket, recv_buffer, '\n');

        std::istream is(&recv_buffer);
        std::getline(is, str_recv);

        //Parsing buffer recv
        std::string address = str_recv.substr(0, str_recv.find(";"));
        if (address.empty())
            return;

        str_recv.erase(0, str_recv.find(";") + 1);
        short port = std::stoi(str_recv.substr(0, str_recv.find(";")));
        if (port == 0)
            return;

        _address = address;
        _port = port;
        
        std::cout << "address : " << _address << " port : " << _port << std::endl;

        boost::system::error_code socket_close_ec;
        _socket.close(socket_close_ec);
        
        return;
}

short Library::TCPClient::getPort() {
    return _port;
}

std::string Library::TCPClient::getAddress() {
    return _address;
}