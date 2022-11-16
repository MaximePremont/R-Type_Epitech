/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_


#include <boost/asio.hpp>
#include <iostream>

#include "Network/includes/UDPServer.hpp"

#include "Server.hpp"
#include "Registry.hpp"

#define SPAWN_TIMING 5
#define BONUS_SPAWN_TIMING 15
#define LEVEL_TIMING 30
#define CONTINUOUS_TIMING 30
#define BOSS_SHOOT_TIMING 2

using boost::asio::ip::udp;

class Server {
    public:
        Server(std::string address, unsigned short port, ECS::Registry &registry);
        void run();
        void stop();
    private:
        void sendLoop();

        void startNetworkServer();
        void ECSLoop();
        void ECSLogic();

        void gameLogic(uint64_t &startGameLogicTiming);
        void levelOne();
        void levelTwo();


        boost::asio::io_service _io_service;
        Library::UDPServer _networkServer;
        ECS::Registry &_registry;
};

#endif /* !SERVER_HPP_ */
