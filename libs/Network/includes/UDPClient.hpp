//
// Created by mikael-vallenet on 26/09/22.
//

#ifndef B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_CLIENT_HPP
#define B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_CLIENT_HPP

#include <deque>
#include <thread>

#include "DataNet.hpp"
#include "Network.hpp"

namespace Library {
class UDPClient : public Network {
public:
    UDPClient(boost::asio::io_context &io_context, std::string address,
        unsigned short port, bool &alive);

    void run();
    void stop();

    void send(const DataNet data, int code);
    void checkSendLoop();

private:
    void receive();
    void handleReceive(const boost::system::error_code& error,
                       std::size_t bytes_transferred);
    
    void handleSend(const boost::system::error_code& error,
                    std::size_t bytes_transferred);

    udp::resolver _resolver;
    
    std::unique_ptr<std::thread> thread_ptr;
    bool &_alive;
};
}  // namespace Library

#endif  // B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_CLIENT_HPP
