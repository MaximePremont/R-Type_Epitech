/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** BgSystem
*/

#pragma once

#include "Registry.hpp"

namespace ECS {
    class BgSystem : public System {
        public:
            BgSystem(Registry & registry);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
    };
}