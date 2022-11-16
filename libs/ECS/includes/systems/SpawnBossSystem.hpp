/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SpawnBossSystem
*/

#pragma once

#include "Registry.hpp"

namespace ECS {
    class SpawnBossSystem : public System {
        public:
            SpawnBossSystem(Registry & registry);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
    };
}
