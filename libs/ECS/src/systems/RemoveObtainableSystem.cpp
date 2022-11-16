/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** RemoveObtainableSystem.cpp
*/

#define BONUS_TIME 10

#include "RemoveObtainableSystem.hpp"

#include "TripleShotComp.hpp"
#include "IgnoreComponent.hpp"

using namespace ECS;

RemoveObtainableSystem::RemoveObtainableSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<Info> RemoveObtainableSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;

    auto const &tripleShooters = _registry.get_components<ECS::TripleShotComp>();

    for (int i = 0; i < tripleShooters.size(); i++) {
        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        auto &tripleShooter = tripleShooters[i];
        if (tripleShooter) {
            auto &vBonus = tripleShooter.value();
            if (time(0) - vBonus.getStartTime() > BONUS_TIME) {
                _registry.remove_component<TripleShotComp>(Entity(i));
            }
        }
    }
    return list;
}
