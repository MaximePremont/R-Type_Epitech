/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** RemoveObtainableSystem.hpp
*/

#pragma once

#include "Registry.hpp"

namespace ECS {
    class RemoveObtainableSystem : public System {
        public:
            RemoveObtainableSystem(Registry & registry);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
    };
}