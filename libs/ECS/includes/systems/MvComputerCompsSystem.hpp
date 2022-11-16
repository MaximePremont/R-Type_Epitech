/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MvComputerCompsSystem
*/

#pragma once

#include "Registry.hpp"

namespace ECS {
    class MvComputerCompsSystem : public System {
        public:
            MvComputerCompsSystem(Registry & registry);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
    };
}
