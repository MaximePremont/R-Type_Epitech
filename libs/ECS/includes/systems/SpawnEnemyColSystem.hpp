/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SpawnEnemyColSystem
*/

#pragma once

#include "Registry.hpp"

namespace ECS {
    class SpawnEnemyColSystem : public System {
        public:
            SpawnEnemyColSystem(Registry & registry);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
    };
}
