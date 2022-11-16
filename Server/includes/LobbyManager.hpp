/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** LobbyManager which handle server
*/

#ifndef LobbyManager_HPP_
#define LobbyManager_HPP_

#include <vector>
#include <sys/types.h>
#include <tuple>
#include <string>

#include "Server.hpp"

#include "Registry.hpp"
#include "Initializer.hpp"

const short MAX_SLOT = 4;

class LobbyManager {
    public:
        LobbyManager(std::string address);
        ~LobbyManager();

        std::string getServer();

    private:
        std::vector<std::tuple<std::string, short, short>> _servers;
        std::string _address;
        short _port;
};

#endif /* !LobbyManager_HPP_ */
