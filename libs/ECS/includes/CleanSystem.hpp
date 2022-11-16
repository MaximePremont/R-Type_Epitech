/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CleanSystem
*/

#pragma once

#include "Registry.hpp"

namespace ECS {
    class CleanSystem : public System {
        public:
            CleanSystem(Registry & registry);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
    };
}
