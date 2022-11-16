/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** FireSystem
*/

#include "FireSystem.hpp"

#include "PositionComponent.hpp"
#include "FireComponent.hpp"
#include "IgnoreComponent.hpp"

using namespace ECS;

FireSystem::FireSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<Info> FireSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;

    auto const &ignores = _registry.get_components<ECS::IgnoreComponent>();
    auto &positions = _registry.get_components<ECS::PositionComponent>();
    auto const &fires = _registry.get_components<ECS::FireComponent>();

    for (int i = 0; i < positions.size() && i < fires.size(); i++) {

        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        auto const &ign = ignores[i];
        if (ign)
            continue;
        auto &pos = positions[i];
        auto const &fire = fires[i];

        if (pos && fire) {
            auto &vpos = pos.value();
            auto const &vfire = fire.value();
            vpos.setX(vpos.getX() + vfire.getSpeed()*4);
            if (vpos.getX() > WINDOW_WIDTH || vpos.getX() < 0) {
                Info inf2(std::type_index(typeid(IgnoreComponent)), i, IgnoreComponent());
                list.push_back(inf2);
                _registry.kill_entity(Entity(i));
                continue;
            }
            PositionComponent modPos(vpos);
            Info inf(std::type_index(typeid(PositionComponent)), i, modPos);
            list.push_back(inf);
        }

    }

    return list;
}
