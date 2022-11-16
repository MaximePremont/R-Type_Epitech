/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** ObtainSystem.cpp
*/

#include "ObtainSystem.hpp"

#include "ObtainableComponent.hpp"
#include "PositionComponent.hpp"
#include "MvmtComponent.hpp"
#include "IgnoreComponent.hpp"
#include "LifeComponent.hpp"
#include "TripleShotComp.hpp"
#include "ComputerComponent.hpp"

using namespace ECS;

ObtainSystem::ObtainSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<Info> ObtainSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;

    auto const &movingEntities = _registry.get_components<ECS::MvmtComponent>();
    auto const &obtainables = _registry.get_components<ECS::ObtainableComponent>();
    auto const &positions = _registry.get_components<ECS::PositionComponent>();
    auto const &computerEntities = _registry.get_components<ECS::ComputerComponent>();

    for (int i = 0; i < movingEntities.size() && i < positions.size(); i++) {
        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        auto &player = movingEntities[i];
        auto &playerPos = positions[i];
        if (player && playerPos) {
            for (int j = 0; j < obtainables.size() && j < positions.size(); j++) {
                auto &obtainable = obtainables[j];
                auto &obtainablePos = positions[j];
                if (obtainable && obtainablePos) {
                    auto &vPlayerPos = playerPos.value();
                    auto &vObtainablePos = obtainablePos.value();
                    if ((vObtainablePos.getX() + vObtainablePos.getW())  >= vPlayerPos.getX() && 
                        vObtainablePos.getY() >= vPlayerPos.getY() &&
                        (vObtainablePos.getY() + vObtainablePos.getH()) <= (vPlayerPos.getY() + vPlayerPos.getH()) &&
                        vObtainablePos.getX() <= (vPlayerPos.getX() + vPlayerPos.getW())) {
                            Info infToDest(std::type_index(typeid(IgnoreComponent)), j, IgnoreComponent());
                            Info inf(std::type_index(typeid(TripleShotComp)), Entity(i), TripleShotComp());
                            _registry.kill_entity(Entity(j));
                            _registry.add_component<TripleShotComp>(Entity(i), TripleShotComp());
                            list.push_back(infToDest);
                            list.push_back(inf);
                    }
                }
            }
        }
    }
    return list;
}
