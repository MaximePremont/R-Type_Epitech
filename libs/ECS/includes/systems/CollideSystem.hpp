/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** CollideSystem.hpp
*/

#pragma once

#include "Registry.hpp"

namespace ECS {
    class CollideSystem : public System {
        public:
            CollideSystem(Registry & registry);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
    };
}