//
// Created by mikael-vallenet on 01/11/22.
//

#include "Lobby.hpp"

Session::Session(tcp::socket socket, std::string network_informations)
    : _socket(std::move(socket)), _network_informations(network_informations) {}

void Session::start() {
    do_read();
}

void Session::do_read() {
    auto self(shared_from_this());

    _socket.async_read_some(boost::asio::buffer(_data, max_length),
                            [this, self](boost::system::error_code ec, std::size_t length) {
                                if (!ec) {
                                    do_write(length);
                                }
                            });
}

void Session::do_write(std::size_t length) {
    auto self(shared_from_this());

    boost::asio::async_write(_socket, boost::asio::buffer(_network_informations, _network_informations.length()),
                             [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                                boost::system::error_code socket_close_ec;
                                _socket.close(socket_close_ec);
                             });
}

Lobby::Lobby(boost::asio::io_context& io_context, short port, std::string address, std::string status)
    : _acceptor(io_context, tcp::endpoint(tcp::v4(), port)), _lobby_manager(LobbyManager(address)), _status(status) {}

void Lobby::do_accept() {
    _acceptor.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket), _lobby_manager.getServer())->start();
            }

            do_accept();
        });
}

bool Lobby::get_status() {
    return !(_status.compare("true"));
}