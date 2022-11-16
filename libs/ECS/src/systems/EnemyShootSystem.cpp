/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemyShootSystem
*/

#include "EnemyShootSystem.hpp"

#include "PositionComponent.hpp"
#include "RectComponent.hpp"
#include "MvmtComponent.hpp"
#include "ShootComponent.hpp"
#include "TextureComponent.hpp"
#include "FireComponent.hpp"
#include "ComputerComponent.hpp"
#include "LazerComponent.hpp"

#include <stdlib.h>

#define LAZER_WIDTH 80
#define LAZER_HEIGHT 16
#define RECT_LAZER_X 267
#define RECT_LAZER_Y 170

using namespace ECS;

EnemyShootSystem::EnemyShootSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<ECS::Info> EnemyShootSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;

    auto const &positions = _registry.get_components<ECS::PositionComponent>();
    auto const &rects = _registry.get_components<ECS::RectComponent>();
    auto const &computerEntities = _registry.get_components<ECS::ComputerComponent>();
    auto const &shoots = _registry.get_components<ECS::ShootComponent>();
    auto const &lazers = _registry.get_components<ECS::LazerComponent>();
    srand(time(NULL));

    for (int i = 0; i < positions.size() && i < rects.size()&& i < computerEntities.size() && i < shoots.size() ; i++) {

        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }

        auto const &pos = positions[i];
        auto const &rect = rects[i];
        auto const &enemy = computerEntities[i];
        auto const &shoot = shoots[i];
        auto const isBoss = lazers[i];

        if (pos && rect && enemy && shoot) {
            auto const vpos = pos.value();
            Entity e = _registry.spawn_entity();
            int x = vpos.getX();
            int y = vpos.getY();
            int fireSpeed = rand() % 5 + 1;
            if (isBoss) {
                _registry.add_component<ECS::PositionComponent>(e, ECS::PositionComponent(x, y, LAZER_WIDTH * 2, LAZER_HEIGHT * 2));
                _registry.add_component<ECS::TextureComponent>(e, ECS::TextureComponent("./assets/r-typesheet1.gif"));
                _registry.add_component<ECS::RectComponent>(e, ECS::RectComponent(RECT_LAZER_X, RECT_LAZER_Y, LAZER_WIDTH, LAZER_HEIGHT));
                Info inf(std::type_index(typeid(ECS::PositionComponent)), e, ECS::PositionComponent(x, y, LAZER_WIDTH * 2, LAZER_HEIGHT * 2));
                list.push_back(inf);
                Info inf2(std::type_index(typeid(ECS::TextureComponent)), e, ECS::TextureComponent("./assets/r-typesheet1.gif"));
                list.push_back(inf2);
                Info inf3(std::type_index(typeid(ECS::RectComponent)), e, ECS::RectComponent(RECT_LAZER_X, RECT_LAZER_Y, LAZER_WIDTH, LAZER_HEIGHT));
                list.push_back(inf3);
            } else {
                _registry.add_component<ECS::PositionComponent>(e, ECS::PositionComponent(x, y, 16, 9));
                _registry.add_component<ECS::TextureComponent>(e, ECS::TextureComponent("./assets/r-typesheet16.gif"));
                _registry.add_component<ECS::RectComponent>(e, ECS::RectComponent(324, 12, 16, 9));
                Info inf(std::type_index(typeid(ECS::PositionComponent)), e, ECS::PositionComponent(x, y, 16, 9));
                list.push_back(inf);
                Info inf2(std::type_index(typeid(ECS::TextureComponent)), e, ECS::TextureComponent("./assets/r-typesheet16.gif"));
                list.push_back(inf2);
                Info inf3(std::type_index(typeid(ECS::RectComponent)), e, ECS::RectComponent(324, 12, 16, 9));
                list.push_back(inf3);
            }
            _registry.add_component<ECS::FireComponent>(e, ECS::FireComponent(-fireSpeed));
            _registry.add_component<ECS::ComputerComponent>(e, ECS::ComputerComponent());
            Info inf4(std::type_index(typeid(ECS::FireComponent)), e, ECS::FireComponent(-fireSpeed));
            list.push_back(inf4);
            Info inf5(std::type_index(typeid(ECS::ComputerComponent)), e, ECS::ComputerComponent());
            list.push_back(inf5);
        }

    }

    return list;
}
