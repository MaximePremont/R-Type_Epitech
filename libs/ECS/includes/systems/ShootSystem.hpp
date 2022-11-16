/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ShootSystem
*/

#pragma once

#include "Registry.hpp"

namespace ECS {
    class ShootSystem : public System {
        public:
            ShootSystem(Registry & registry);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
    };
}
