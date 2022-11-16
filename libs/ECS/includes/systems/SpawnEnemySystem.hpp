/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SpawnEnemySystem
*/

#pragma once

#include "Registry.hpp"

namespace ECS {
    class SpawnEnemySystem : public System {
        public:
            SpawnEnemySystem(Registry & registry);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
    };
}
