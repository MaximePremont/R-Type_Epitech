/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Network
*/

#include "Network.hpp"

/**
 * Network constructor
 * 
 * The network is the higher class into the lib
 * 
 * @param io_context a simple io_context
 */
Library::Network::Network(boost::asio::io_context &io_context, std::string address, unsigned short port) :
    _io_service(io_context),
    _socket(io_context),
    _address(std::move(address)),
    _port(port),
    _datanetToRead(std::deque<DataNet>()),
    _datanetToSend(std::deque<DataNet>())
{
    _socket.open(udp::v4());
}

/**
 * Get the DataNet to read queue size
 * 
 * @returns DataNet to read queue size
 */
std::size_t Library::Network::getQueueSizeToRead() {
    return _datanetToRead.size();
}

/**
 * Push a DataNet into the queue
 * 
 * @param dataNet which have to be push into the queue
 */
void Library::Network::pushDatanetToRead(DataNet dataNet) {
    _datanetToRead.push_back(dataNet);
}

/**
 * Pop the first DataNet of the queu
 * 
 * @returns the first DataNet
 */
std::optional<DataNet> Library::Network::popDatanetToRead() {
    if (_datanetToRead.size() <= 0)
        return std::nullopt;
    try {
        DataNet dataNet = _datanetToRead.front();
        _datanetToRead.pop_front();
        return dataNet;
    } catch(const std::exception& e) {
        (void) e;
        return std::nullopt;
    }
}

/**
 * Get the DataNet to send queue size
 * 
 * @returns DataNet to send queue size
 */
std::size_t Library::Network::getQueueSizeToSend() {
    return _datanetToSend.size();
}

/**
 * Push a DataNet into the queue
 * 
 * @param dataNet which have to be push into the queue
 */
void Library::Network::pushDatanetToSend(DataNet dataNet) {
    try {
        DataNet d(dataNet);
        _datanetToSend.push_back(d);
    } catch(const std::exception& e) {
        (void) e;
    }
}

/**
 * Push a DataNet into the queue
 * 
 * @returns dataNet which have been pop from the queue
 */
std::optional<DataNet> Library::Network::popDatanetToSend() {
    if (_datanetToSend.size() <= 0)
        return std::nullopt;
    try {
        DataNet data(_datanetToSend.front());
        _datanetToSend.pop_front();
        return data;
    } catch(const std::exception& e) {
        (void) e;
        return std::nullopt;
    }
}

/**
 * Set port
 * 
 * @param port the port to assigne
 */
void Library::Network::setPort(const unsigned short port) {
    _port = port;
}

/**
 * Set address
 * 
 * @param address the address to assigne
 */
void Library::Network::setAddress(const std::string address) {
    _address = address;
}

/**
 * Get current port
 * 
 * @returns the current port
 */
[[nodiscard]] unsigned short Library::Network::getPort() const { return _port; }

/**
 * Get current address
 * 
 * @returns the current address
 */
[[nodiscard]] std::string Library::Network::getAddress() const { return _address; }


/**
 * Writing RFC code into 1 bytes, 1 bit for error and 7 bits for message
 * 
 * @param code the code to compress into one byte
 * @returns the byte which contains the RFC code compressed
 */
unsigned char binarize_code(int code) {
    int mask = 1 << 7;

    return ((code % 10 & ~mask) | (code / 10 << 7));
}
