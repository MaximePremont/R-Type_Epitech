/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ShipMvLSystem
*/

#include <any>

#include "ShipMvLSystem.hpp"
#include "MvmtComponent.hpp"
#include "PositionComponent.hpp"
#include "RectComponent.hpp"

using namespace ECS;

ShipMvLSystem::ShipMvLSystem(ECS::Registry & registry) :
    _registry(registry)
{}

std::vector<Info> ShipMvLSystem::callSystem(std::vector<std::any> & params) {
    std::vector<Info> map;

    auto &positions = _registry.get_components<ECS::PositionComponent>();
    auto &rectangles = _registry.get_components<ECS::RectComponent>();
    auto const &moving = _registry.get_components<ECS::MvmtComponent>();

    for (int i = 0; i < positions.size() && i < moving.size() && i < rectangles.size(); i++) {
        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        auto &pos = positions[i];
        auto &rect = rectangles[i];
        auto const &move = moving[i];
        
        if (pos && move && rect) {
            auto &vpos = pos.value();
            auto &vrect = rect.value();
            auto const &vmove = move.value();
            if (vpos.getX() - vmove.getSpeed() >= 0) {
                vpos.setX(vpos.getX() - vmove.getSpeed());
                vrect.setX(SHIP_LEFT_X);
                PositionComponent modPos(vpos);
                RectComponent modRect(vrect);
                ECS::Info modInf(std::type_index(typeid(PositionComponent)), i, modPos);
                map.push_back(modInf);
                ECS::Info modInf2(std::type_index(typeid(RectComponent)), i, modRect);
                map.push_back(modInf2);
            }
        }
    }
    return map;
}
