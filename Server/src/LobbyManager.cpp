/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** LobbyManager which handle server
*/

#include "LobbyManager.hpp"

LobbyManager::LobbyManager(std::string address) : _address(address), _port(1025)
{
}

LobbyManager::~LobbyManager()
{
}

std::string LobbyManager::getServer()
{
    int nb_server = 1;

    //Check for an running server with slot available
    for (auto & server : _servers) {
        if (std::get<2>(server) < MAX_SLOT) {
            std::get<2>(server) += 1;
            std::cout << "Player " << std::get<2>(server) << " join the server " << nb_server << std::endl;
            return std::get<0>(server) + ";" + std::to_string(std::get<1>(server)) + "\n";
        }
        nb_server += 1;
    }

    //Launch a new server
    std::tuple<std::string, short, short> new_server(_address, _port, 1);
    _servers.push_back(new_server);

    _port += 1;
    std::cout << "\nLaunching server " <<  nb_server << " at address " << std::get<0>(new_server) << ":" << std::get<1>(new_server) << "\n" << std::endl;
    std::cout << "Player " << std::get<2>(new_server) << " join the server " << nb_server << std::endl;

    pid_t pid;
    pid = fork();
    if (pid == 0) {
        ECS::Registry registry;
        ECS::Initializer initializer(registry);

        initializer.init_components();
        initializer.init_system();
        initializer.init_setup();

        Server udp_server(std::get<0>(new_server), std::get<1>(new_server), registry);
        udp_server.run();
        EXIT_SUCCESS;
    }

    return std::get<0>(new_server) + ";" + std::to_string(std::get<1>(new_server)) + "\n";
}
