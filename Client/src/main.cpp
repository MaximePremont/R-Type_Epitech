/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** main.cpp
*/

#include <cstdlib>
#include <csignal>
#include <iostream>

#include "Game.hpp"

/**
 * Handle interruption signal and exit properly
 *
 * @param signum is the value of the signal received
 */
void signalHandler(int signum) {
    exit(0);
}

/**
 * Entrypoint of the client
 *
 * @param argc the arguments count
 * @param argv the arguments values
 * @returns the code which indicates if program fails or succeed
 */
int main(int argc, char **argv) {

    signal(SIGINT, signalHandler);

    if (argc < 4 || argc > 5 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        std::cout << "USAGE: ./server <address> <port> <sound> <lobby_status>" << std::endl;
        return 0;
    }

    std::string address = argv[1];
    short port = std::atoi(argv[2]);
    short sound = std::atoi(argv[3]);
    std::string lobby_status = (argc == 5) ? argv[4] : "false";

    if (!lobby_status.compare("true")) {    
        boost::asio::io_context io_context;
        Library::TCPClient client(io_context, argv[1], argv[2]);
        client.getServer();
        port = client.getPort();
        address = client.getAddress();
        sleep(1);
    }
    
    Client::Game g(port, address, sound);
    g.start();

    return EXIT_SUCCESS;
}
