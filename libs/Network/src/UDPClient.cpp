/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** Client
*/

#include "UDPClient.hpp"

/**
 * Client constructor
 * 
 * The client is the object which allows to communicate with server
 * 
 * @param io_context a simple io_context
 * @param port the port to bind
 * @param address the address to bind
 * @param alive bool of life
 */
Library::UDPClient::UDPClient(boost::asio::io_context &io_context, std::string address, unsigned short port, bool &alive) :
    Network(io_context, address, port),
    _resolver(io_context),
    _alive(alive)
{
}

/**
 * Start the thread which allows the client to run
 */
void Library::UDPClient::run() {
    _receiver_endpoint =
        *_resolver.resolve(udp::v4(), getAddress(), std::to_string(getPort())).begin();
    if (_alive)
        receive();
}

void Library::UDPClient::stop() {
    _socket.close();
}

/**
 * Register the receive handler
 */
void Library::UDPClient::receive() {
    _recv_buffer.resize(4096);
    _socket.async_receive_from(
        boost::asio::buffer(_recv_buffer), _receiver_endpoint,
        boost::bind(&Library::UDPClient::handleReceive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

/**
 * Callback trigger when receive handler is call
 * 
 * @param error the error code which indicates if the receive is successful
 * @param bytes_transferred the number of bytes received
 */
void Library::UDPClient::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred) {
    (void)bytes_transferred;  // UNUSED
    if (error) return;
    unsigned char code = _recv_buffer[0];
    if (code == 9) {
        _alive = false;
        return;
    }
    (void)code;  // contains the rfc code
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
    if (_alive)
        receive();
}

/**
 * Send DataNet to the server
 * 
 * @param data the DataNet to be sent
 * @param code the RFC code to be sent with the DataNet
 */
void Library::UDPClient::send(const DataNet data, int code) {
    char code_buffer = binarize_code(code);
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << data;
    _socket.async_send_to(
        boost::asio::buffer(code_buffer + archive_stream.str()),
        _receiver_endpoint,
        boost::bind(&UDPClient::handleSend, this, boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

/**
 * Callback trigger when send function is call
 * 
 * @param error the error code which indicates if the send is successful
 * @param bytes_transferred the number of bytes sent
 */
void Library::UDPClient::handleSend(const boost::system::error_code &error, std::size_t bytes_transferred) {
    if (error) return;
    (void) bytes_transferred;
}

/**
 * Check if a DataNet has to be push
 */
void Library::UDPClient::checkSendLoop() {
    while(getQueueSizeToSend()) {
        if (!_alive)
            return;
        std::optional<DataNet> odata = popDatanetToSend();
        if (odata)
            send(odata.value(), 1);
    }
}
