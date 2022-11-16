/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MvComputerCompsSystem
*/

#include "MvComputerCompsSystem.hpp"

#include "MvmtComponent.hpp"
#include "PositionComponent.hpp"
#include "ComputerComponent.hpp"

#include <stdlib.h>

using namespace ECS;

MvComputerCompsSystem::MvComputerCompsSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<ECS::Info> MvComputerCompsSystem::callSystem(std::vector<std::any> & params) {
    std::vector<Info> map;

    auto &positions = _registry.get_components<ECS::PositionComponent>();
    auto const &moving = _registry.get_components<ECS::MvmtComponent>();
    auto const &computerEntities = _registry.get_components<ECS::ComputerComponent>();

    for (int i = 0; i < positions.size() && i < moving.size(); i++) {
        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        
        auto &pos = positions[i];
        auto const &move = moving[i];
        auto const &computerComp = computerEntities[i];

        if (pos && move && computerComp) {
            auto &vpos = pos.value();
            auto const &vmove = move.value();
            if (vpos.getX() - vmove.getSpeed() >= 0) {
                vpos.setX(vpos.getX() - vmove.getSpeed());
                PositionComponent modPos(vpos);
                ECS::Info modInf(std::type_index(typeid(PositionComponent)), i, modPos);
                map.push_back(modInf);
            }
        }
    }
    return map;
}
