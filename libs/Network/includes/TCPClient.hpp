//
// Created by mikael-vallenet on 01/11/22.
//

#ifndef B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_TCPCLIENT_HPP
#define B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_TCPCLIENT_HPP

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace Library {

    class TCPClient {

    public:

        TCPClient(boost::asio::io_context& io_context, std::string address, std::string port);
        
        void getServer();
        short getPort();
        std::string getAddress();

    private:

        tcp::socket _socket;
        tcp::resolver _resolver;
        enum { max_length = 1024 };

        std::string _address;
        short _port;
        };
}

#endif  // B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_TCPCLIENT_HPP
