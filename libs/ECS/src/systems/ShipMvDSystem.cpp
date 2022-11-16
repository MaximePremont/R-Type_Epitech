/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ShipMvDSystem
*/

#include <any>

#include "ShipMvDSystem.hpp"
#include "MvmtComponent.hpp"
#include "PositionComponent.hpp"

using namespace ECS;

ShipMvDSystem::ShipMvDSystem(ECS::Registry & registry) :
    _registry(registry)
{}

std::vector<Info> ShipMvDSystem::callSystem(std::vector<std::any> & params) {
    std::vector<Info> map;

    auto &positions = _registry.get_components<ECS::PositionComponent>();
    auto const &moving = _registry.get_components<ECS::MvmtComponent>();

    for (int i = 0; i < positions.size() && i < moving.size(); i++) {
        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        
        auto &pos = positions[i];
        auto const &move = moving[i];

        if (pos && move) {
            auto &vpos = pos.value();
            auto const &vmove = move.value();
            if (vpos.getY() + vpos.getH() + vmove.getSpeed() <= WINDOW_HEIGHT) {
                vpos.setY(vpos.getY() + vmove.getSpeed());
                PositionComponent modPos(vpos);
                ECS::Info modInf(std::type_index(typeid(PositionComponent)), i, modPos);
                map.push_back(modInf);
            }
        }
    }
    return map;
}
