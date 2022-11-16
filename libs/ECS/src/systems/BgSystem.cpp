/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** BgSystem
*/

#include "BgSystem.hpp"

#include "PositionComponent.hpp"

using namespace ECS;

BgSystem::BgSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<ECS::Info> BgSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;

    auto &positions = _registry.get_components<ECS::PositionComponent>();

    for (int i = 4; i < 6 && i < positions.size(); i++) {
        auto &pos = positions[i];
        if (pos) {
            auto &vpos = pos.value();
            vpos.setX(vpos.getX() - 1);
            if (vpos.getX() < -5449)
                vpos.setX(5449);
        }
    }

    return list;
}