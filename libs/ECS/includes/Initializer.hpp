/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Initializer
*/

#pragma once

#include <unordered_map>

#include "Registry.hpp"

#define PLAYER_LIVES 3

namespace ECS {
    class Initializer {
        public:
            /**
             * Initializer constructor
             * 
             * Initializer is used to register the complete game logic
             * in the registry at starting.
             * 
             * @param registry Registry to complete
             */
            Initializer(Registry & registry);

            /**
             * Init components for game logic
             */
            void init_components();
            /**
             * Init systems for game logic
             */
            void init_system();
            /**
             * Init all components
             * 
             * Must be called in the server, only after the init of compoents and systems
             */
            void init_setup();
            void init_menu();
        private:
            Registry & _registry;

            void register_users();
    };
}
