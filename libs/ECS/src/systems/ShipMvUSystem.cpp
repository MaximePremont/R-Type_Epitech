/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ShipMvUSystem
*/

#include <any>

#include "ShipMvUSystem.hpp"
#include "MvmtComponent.hpp"
#include "PositionComponent.hpp"

using namespace ECS;

ShipMvUSystem::ShipMvUSystem(ECS::Registry & registry) :
    _registry(registry)
{}

std::vector<Info> ShipMvUSystem::callSystem(std::vector<std::any> & params) {
    std::vector<Info> map;

    auto &positions = _registry.get_components<ECS::PositionComponent>();
    auto const &moving = _registry.get_components<ECS::MvmtComponent>();

    for (int i = 0; i < positions.size() && i < moving.size(); i++) {
        if (params.size() != 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        auto &pos = positions[i];
        auto const &move = moving[i];
        
        if (pos && move) {
            auto &vpos = pos.value();
            auto const &vmove = move.value();
            if (vpos.getY() - vmove.getSpeed() >= 0) {
                vpos.setY(vpos.getY() - vmove.getSpeed());
                PositionComponent modPos(vpos);
                ECS::Info modInf(std::type_index(typeid(PositionComponent)), i, modPos);
                map.push_back(modInf);
            }
        }
    }
    return map;
}
