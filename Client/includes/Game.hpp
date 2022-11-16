/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Game
*/

#pragma once

#include <memory>
#include <type_traits>

#include "Registry.hpp"
#include "Network/includes/UDPClient.hpp"
#include "Network/includes/TCPClient.hpp"
#include "Graphics.hpp"

namespace Client {
    class Game {
        public:
            Game(unsigned short port, std::string address, int const sound);

            void start();
            void stop();
            Uint64 getTicks();
            Uint64 last_shoot;
            void ECSLoop();
            void startNetworkClient();
            // ECS //
            template <class SystemT>
            std::vector<ECS::Info> subCallSystem(std::vector<std::any> params) {
                DataNet data(_user_id, std::type_index(typeid(SystemT)), 0);
                _networkClient.pushDatanetToSend(data);
                return _registry.call_system<SystemT>(params);
            }
            Graphics::GraphSystem &getGraphics();
            bool _init;
            ECS::Registry _registry;
        private:
            const int _sound;
            Graphics::GraphSystem _graphics;
            bool _alive;
            int _user_id;
            // Network //
            boost::asio::io_service _io_service;
            Library::UDPClient _networkClient;
    };
}
