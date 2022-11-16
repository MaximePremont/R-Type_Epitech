/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** Server
*/

#include "UDPServer.hpp"
#include <utility>

/**
 * Server constructor
 * 
 * The server is the object which allows to communicate with clients
 * 
 * @param io_context a simple io_context
 * @param port the port to bind
 * @param address the address to bind
 * @param registry the ECS registry
 */
Library::UDPServer::UDPServer(boost::asio::io_context &io_context, std::string address, unsigned short port, ECS::Registry &registry) :
    Network(io_context, address, port),
    _registry(registry)
{
    _socket.bind(udp::endpoint(udp::v4(), getPort()));
    std::cout << "Server initialized successful" << std::endl;
}

/**
 * Server destructor
 */
Library::UDPServer::~UDPServer() = default;

void Library::UDPServer::run() {
    receive();
}

void Library::UDPServer::stop() {
    DataNet data(0, std::type_index(typeid(int)), 0);
    sendToAll(data, 9);
    sleep(1);
    _socket.close();
}

/**
 * Register the receive handler
 */
void Library::UDPServer::receive() {
    _recv_buffer.resize(4096);
    _socket.async_receive_from(
        boost::asio::buffer(_recv_buffer), _receiver_endpoint,
        boost::bind(&Library::UDPServer::handleReceive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

/**
 * Callback trigger when receive handler is call
 * 
 * @param error the error code which indicates if the receive is successful
 * @param bytes_transferred the number of bytes received
 */
void Library::UDPServer::handleReceive(const boost::system::error_code &error,
                                    std::size_t bytes_transferred) {
    if (error) {
        std::cout << "Error in HandleReceive" << std::endl;
        return;
    }
    if (std::find(_clientsEndpoint.begin(), _clientsEndpoint.end(), _receiver_endpoint) == _clientsEndpoint.end()) {
        std::cout << "Client connected: " << _receiver_endpoint.address() << ":" << _receiver_endpoint.port() << std::endl;
        _clientsEndpoint.push_back(std::move(_receiver_endpoint));
        std::vector<ECS::Info> changedComponents = _registry.getConnectComponents();
        for (std::size_t i = 0; i < changedComponents.size(); i++) {
            ECS::Info &inf = changedComponents[i];
            DataNet data(inf._value, inf._index, inf._any);
            std::ostringstream archive_stream;
            boost::archive::text_oarchive archive(archive_stream);
            archive << data;
            asyncSendToEndpoint(archive_stream.str(), _receiver_endpoint);
        }
        _recv_buffer.clear();
        receive();
        return;
    }
    unsigned char code = _recv_buffer[0];
    if (code == 9) {
        std::cout << "Client disconnected: " << _receiver_endpoint.address() << ":" << _receiver_endpoint.port() << std::endl;
        _clientsEndpoint.erase(std::remove(_clientsEndpoint.begin(), _clientsEndpoint.end(), _receiver_endpoint), _clientsEndpoint.end());
        return;
    }
    _recv_buffer.erase(0, 1);
    try {
        std::istringstream archive_stream(_recv_buffer);
        boost::archive::text_iarchive archive(archive_stream);
        DataNet data(0, std::type_index(typeid(int)), 0);
        archive >> data;
        pushDatanetToRead(data);
    } catch(const std::exception& e) {
        (void) e;
    }
    _recv_buffer.clear();
    receive();
}

/**
 * Send string to a defined endpoint
 * 
 * @param data the data to be sent
 * @param endpoint the endpoint where the data must be send
 */
void Library::UDPServer::asyncSendToEndpoint(std::string data,
                                          udp::endpoint &endpoint) {
    char code_buffer = binarize_code(1);
    _socket.async_send_to(
        boost::asio::buffer(code_buffer + data), endpoint,
        boost::bind(&Library::UDPServer::handleSend, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

/**
 * Send DataNet to all clients
 * 
 * @param data the DataNet to be sent
 * @param code the RFC code to be sent with the DataNet
 */
void Library::UDPServer::sendToAll(const DataNet data, int code) {
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << data;
    for (udp::endpoint &endpoint : _clientsEndpoint) {
        asyncSendToEndpoint(archive_stream.str(), endpoint);
    }
}

/**
 * Callback trigger when send function is call
 * 
 * @param error the error code which indicates if the send is successful
 * @param bytes_transferred the number of bytes sent
 */
void Library::UDPServer::handleSend(const boost::system::error_code &error,
                                 std::size_t bytes_transferred) {
    if (error) return;
    (void) bytes_transferred;
}

/**
 * Check if a DataNet has to be push
 */
void Library::UDPServer::checkSendLoop() {
    while(getQueueSizeToSend() > 0) {
        std::optional<DataNet> odata = popDatanetToSend();
        if (odata)
            sendToAll(odata.value(), 1);
    }
}
