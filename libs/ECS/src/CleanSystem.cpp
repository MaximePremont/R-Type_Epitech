/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CleanSystem
*/

#include "CleanSystem.hpp"

#include "IgnoreComponent.hpp"

using namespace ECS;

CleanSystem::CleanSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<Info> CleanSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;

    auto const &ignores = _registry.get_components<ECS::IgnoreComponent>();

    for (int i = 0; i < ignores.size(); i++) {

        auto const &ign = ignores[i];
        if (ign)
            _registry.kill_entity(Entity(i));

    }

    return list;
}
