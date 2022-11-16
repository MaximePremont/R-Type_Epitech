/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** FireSystem
*/

#pragma once

#include "Registry.hpp"

namespace ECS {
    class FireSystem : public System {
        public:
            FireSystem(Registry & registry);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
    };
}
