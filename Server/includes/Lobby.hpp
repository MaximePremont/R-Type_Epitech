//
// Created by mikael-vallenet on 01/11/22.
//

#ifndef B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_Lobby_HPP
#define B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_Lobby_HPP

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "LobbyManager.hpp"

using boost::asio::ip::tcp;

class Session
    : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, std::string network_informations);
    void start();

private:
    void do_read();
    void do_write(std::size_t length);

    tcp::socket _socket;
    enum { max_length = 1024 };
    char _data[max_length];
    std::string _network_informations;
};

class Lobby
{
public:
    Lobby(boost::asio::io_context& io_context, short port, std::string address, std::string status);

    void do_accept();
    bool get_status();

private:

    tcp::acceptor _acceptor;
    std::string _status;
    LobbyManager _lobby_manager;
};

#endif  // B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_Lobby_HPP