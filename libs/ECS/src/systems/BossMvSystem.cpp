/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** BossMvSystem
*/

#include <any>

#include "BossMvSystem.hpp"
#include "EnMvmtComponent.hpp"
#include "LazerComponent.hpp"
#include "PositionComponent.hpp"

using namespace ECS;

BossMvSystem::BossMvSystem(ECS::Registry & registry) :
    _registry(registry)
{}

std::vector<Info> BossMvSystem::callSystem(std::vector<std::any> & params) {
    std::vector<Info> map;

    auto &positions = _registry.get_components<ECS::PositionComponent>();
    auto &moving = _registry.get_components<ECS::EnMvmtComponent>();
    auto const &lazers = _registry.get_components<ECS::LazerComponent>();

    for (int i = 0; i < positions.size() && i < moving.size() && i < lazers.size(); i++) {
        if (params.size() != 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        auto &pos = positions[i];
        auto &move = moving[i];
        auto const &boss = lazers[i];
        
        if (pos && move && boss) {
            auto &vpos = pos.value();
            auto &vmove = move.value();
            int posY = vpos.getY();
            int speed = vmove.getSpeed();
            if (posY + speed >= 0 && posY + vpos.getH() + speed <= WINDOW_HEIGHT) {
                vpos.setY(posY + speed);
                PositionComponent modPos(vpos);
                ECS::Info modInf(std::type_index(typeid(PositionComponent)), i, modPos);
                map.push_back(modInf);
            } else {
                vmove.setSpeed(-speed);
                EnMvmtComponent modMv(vmove);
                ECS::Info modInf(std::type_index(typeid(EnMvmtComponent)), i, modMv);
                map.push_back(modInf);
            }
        }
    }
    return map;
}
