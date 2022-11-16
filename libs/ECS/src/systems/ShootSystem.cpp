/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ShootSystem
*/

#include "ShootSystem.hpp"

#include "PositionComponent.hpp"
#include "RectComponent.hpp"
#include "MvmtComponent.hpp"
#include "ShootComponent.hpp"
#include "TextureComponent.hpp"
#include "FireComponent.hpp"
#include "TripleShotComp.hpp"

using namespace ECS;

ShootSystem::ShootSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<ECS::Info> ShootSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;

    auto const &positions = _registry.get_components<ECS::PositionComponent>();
    auto const &rects = _registry.get_components<ECS::RectComponent>();
    auto const &mvmts = _registry.get_components<ECS::MvmtComponent>();
    auto const &shoots = _registry.get_components<ECS::ShootComponent>();
    auto const &tripleShooters = _registry.get_components<ECS::TripleShotComp>();
    int nbShots = 1;

    for (int i = 0; i < positions.size() && i < rects.size(); i++) {

        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }

        auto const &pos = positions[i];
        auto const &rect = rects[i];
        auto const &mvmt = mvmts[i];
        auto const &shoot = shoots[i];
        auto const &tripleShoots = tripleShooters[i];
        if (pos && rect && mvmt && shoot) {
            if (tripleShoots)
                nbShots = 3;
            auto const &vpos = pos.value();
            int x = vpos.getX();
            int y = vpos.getY();
            for (; nbShots; nbShots--, x += 56) {
                Entity e = _registry.spawn_entity();
                _registry.add_component<ECS::PositionComponent>(e, ECS::PositionComponent(x, y, 51, 51));
                _registry.add_component<ECS::TextureComponent>(e, ECS::TextureComponent("./assets/r-typesheet30a.gif"));
                _registry.add_component<ECS::RectComponent>(e, ECS::RectComponent(0, 0, 34, 34));
                _registry.add_component<ECS::FireComponent>(e, ECS::FireComponent(5));
                Info inf(std::type_index(typeid(ECS::PositionComponent)), e, ECS::PositionComponent(x, y, 51, 51));
                list.push_back(inf);
                Info inf2(std::type_index(typeid(ECS::TextureComponent)), e, ECS::TextureComponent("./assets/r-typesheet30a.gif"));
                list.push_back(inf2);
                Info inf3(std::type_index(typeid(ECS::RectComponent)), e, ECS::RectComponent(0, 0, 34, 34));
                list.push_back(inf3);
                Info inf4(std::type_index(typeid(ECS::FireComponent)), e, ECS::FireComponent(5));
                list.push_back(inf4);
            }
        }

    }

    return list;
}
