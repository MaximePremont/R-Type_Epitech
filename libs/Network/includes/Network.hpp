//
// Created by mikael-vallenet on 26/09/22.
//

#ifndef B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_NETWORK_HPP
#define B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_NETWORK_HPP

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <deque>
#include <iostream>
#include <cstddef>
#include <optional>

#include "DataNet.hpp"
#include "Registry.hpp"

using boost::asio::ip::address;
using boost::asio::ip::udp;

enum RFC_CODE {
    KO = 0,
    OK = 10,
    FIRST_CONNECTION = 11,
    DATANET_TRANSMISSION = 12,
};

unsigned char binarize_code(int code);

namespace Library {
class Network {
public:
    Network(boost::asio::io_context& io_context, std::string address, unsigned short port);

    void setPort(unsigned short port);
    void setAddress(const std::string address);
    [[nodiscard]] unsigned short getPort() const;
    [[nodiscard]] std::string getAddress() const;

    // DataNet Read //
    std::size_t getQueueSizeToRead();
    void pushDatanetToRead(DataNet dataNet);
    std::optional<DataNet> popDatanetToRead();

    // DataNet Send //
    std::size_t getQueueSizeToSend();
    void pushDatanetToSend(DataNet dataNet);
    std::optional<DataNet> popDatanetToSend();

protected:
    udp::socket _socket;
    udp::endpoint _receiver_endpoint;
    std::string _recv_buffer;

private:
    void receive();
    void handleReceive(const boost::system::error_code& error,
                       std::size_t bytes_transferred);
    void send();
    void handleSend(const boost::system::error_code& error,
                    std::size_t bytes_transferred);

    // Variables //
    unsigned short _port;
    std::string _address;
    std::deque<DataNet> _datanetToSend;
    std::deque<DataNet> _datanetToRead;
    
    boost::asio::io_service& _io_service;
};
}  // namespace Library

#endif  // B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_NETWORK_HPP
