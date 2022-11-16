/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** main
*/

#include "Lobby.hpp"
#include "Server.hpp"
#include "DataNet.hpp"
#include <thread>
#include <iostream>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/write.hpp>
#include<sys/types.h>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <memory>

#include "Registry.hpp"
#include "Initializer.hpp"

/**
 * Handle interruption signal and exit properly
 *
 * @param signum is the value of the signal received
 */
void signalHandler(int signum) {
    exit(0);
}

/**
 * Entrypoint of the server
 *
 * @param argc the arguments count
 * @param argv the arguments values
 * @returns the code which indicates if program fails or succeed
 */
int main(int argc, char **argv) {

    signal(SIGINT, signalHandler);

    if (argc < 3 || argc > 4 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        std::cout << "USAGE: ./server <address> <port> <lobby_status>" << std::endl;
        return 0;
    }

    std::string address = argv[1];
    short port = std::atoi(argv[2]);
    std::string lobby_status = (argc == 4) ? argv[3] : "false";

    boost::asio::io_context io_context;
    Lobby lobby(io_context, std::atoi(argv[2]), argv[1], lobby_status);

    if (lobby.get_status()) {
        lobby.do_accept();
        io_context.run();
    } else {
        ECS::Registry registry;
        ECS::Initializer initializer(registry);

        initializer.init_components();
        initializer.init_system();
        initializer.init_setup();

        Server udp_server(address, port, registry);
        udp_server.run();
    }

    return EXIT_SUCCESS;
}
