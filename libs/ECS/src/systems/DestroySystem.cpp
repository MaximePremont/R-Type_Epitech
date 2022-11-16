/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** DestroySystem.cpp
*/

#include "DestroySystem.hpp"

#include "FireComponent.hpp"
#include "PositionComponent.hpp"
#include "IgnoreComponent.hpp"
#include "LifeComponent.hpp"
#include "ComputerComponent.hpp"

using namespace ECS;

DestroySystem::DestroySystem(Registry & registry) :
    _registry(registry)
{}

std::vector<Info> DestroySystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;

    auto const &fires = _registry.get_components<ECS::FireComponent>();
    auto &leavingEntities = _registry.get_components<ECS::LifeComponent>();
    auto const &positions = _registry.get_components<ECS::PositionComponent>();
    auto const &computerEntities = _registry.get_components<ECS::ComputerComponent>();

    for (int i = 0; i < fires.size() && i < positions.size(); i++) {
        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        auto &fire = fires[i];
        auto &isEnemy = computerEntities[i];
        if (fire) {
            for (int j = 0; j < leavingEntities.size() && i < positions.size() && i < computerEntities.size(); j++) {
                auto &target = leavingEntities[j];
                auto &targetPos = positions[j];
                auto &targetIsEnemy = computerEntities[j];
                auto &firePos = positions[i];
                if (target && firePos && targetPos && ((isEnemy && !targetIsEnemy) || (!isEnemy && targetIsEnemy))) {
                    auto &vTarget = target.value();
                    auto &vTargetPos = targetPos.value();
                    auto &vFirePos = firePos.value();
                    int fireX = vFirePos.getX();
                    int fireY = vFirePos.getY();
                    int fireW = vFirePos.getW();
                    int fireH = vFirePos.getH();
                    int targetX = vTargetPos.getX();
                    int targetY = vTargetPos.getY();
                    int targetW = vTargetPos.getW();
                    int targetH = vTargetPos.getH();
                    if (((fireX  + fireW >= targetX ) &&
                        (fireX <= targetX + targetW)) &&
                        (((fireY >= targetY) && (fireY <= targetY + targetH)) ||
                        ((fireY + fireH >= targetY) && (fireY + fireH <= targetY + targetH)))) {
                            if ((j < 4 && j < _registry.getNumberUsers()) || j >= 4) {
                                vTarget.setLives(vTarget.getLives() - 1);
                                Info infFire(std::type_index(typeid(IgnoreComponent)), i, IgnoreComponent());
                                _registry.kill_entity(Entity(i));
                                list.push_back(infFire);
                            }
                    }
                    if (!vTarget.getLives()) {
                        Info infToDest(std::type_index(typeid(IgnoreComponent)), j, IgnoreComponent());
                        list.push_back(infToDest);
                        _registry.kill_entity(Entity(j));
                        continue;
                    }
                    LifeComponent modTarget(vTarget);
                    Info inf(std::type_index(typeid(LifeComponent)), j, modTarget);
                    list.push_back(inf);
                }
            }
        }
    }
    return list;
}
