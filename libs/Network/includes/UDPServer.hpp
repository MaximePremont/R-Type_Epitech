//
// Created by mikael-vallenet on 26/09/22.
//

#ifndef B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_SERVER_HPP
#define B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_SERVER_HPP

#include <deque>
#include <boost/asio.hpp>
#include <stdexcept>

#include "DataNet.hpp"
#include "Network.hpp"

#include "Registry.hpp"

namespace Library {

class UDPServer : public Network {
public:
    UDPServer(boost::asio::io_context& io_context, std::string address,
        unsigned short port, ECS::Registry &_registry);
    ~UDPServer();

    void run();
    void stop();

    void sendToAll(const DataNet data, int code);
    void checkSendLoop();

private:
    void receive();
    void handleReceive(const boost::system::error_code& error,
                       std::size_t bytes_transferred);

    void asyncSendToEndpoint(std::string data, udp::endpoint& endpoint);
    void handleSend(const boost::system::error_code& error,
                    std::size_t bytes_transferred);

    std::vector<boost::asio::ip::udp::endpoint> _clientsEndpoint;

    std::unique_ptr<std::thread> thread_ptr;

    ECS::Registry &_registry;
};
}  // namespace Library

#endif  // B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_SERVER_HPP
