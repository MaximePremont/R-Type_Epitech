/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemyShootSystem
*/

#pragma once

#include "Registry.hpp"

namespace ECS {
    class EnemyShootSystem : public System {
        public:
            EnemyShootSystem(Registry & registry);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
    };
}
