/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** DestroySystem.hpp
*/

#pragma once

#include "Registry.hpp"

namespace ECS {
    class DestroySystem : public System {
        public:
            DestroySystem(Registry & registry);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
    };
}