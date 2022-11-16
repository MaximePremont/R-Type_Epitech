/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SpawnEnemy
*/

#include "SpawnEnemySystem.hpp"

#include "PositionComponent.hpp"
#include "RectComponent.hpp"
#include "TextureComponent.hpp"
#include "DestroyableComponent.hpp"
#include "ShootComponent.hpp"
#include "LifeComponent.hpp"
#include "ComputerComponent.hpp"

#include <stdlib.h>

using namespace ECS;

SpawnEnemySystem::SpawnEnemySystem(Registry & registry) :
    _registry(registry)
{}

std::vector<ECS::Info> SpawnEnemySystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;
        srand (time(NULL));
        int posX = rand() % (WINDOW_WIDTH / 2) - ENEMY_WIDTH + (WINDOW_WIDTH / 2);
        int posY = rand() % (WINDOW_HEIGHT - ENEMY_HEIGHT) + 0;

        Entity e = _registry.spawn_entity();
        _registry.add_component<ECS::PositionComponent>(e, ECS::PositionComponent(posX, posY, ENEMY_WIDTH, ENEMY_HEIGHT));
        _registry.add_component<ECS::TextureComponent>(e, ECS::TextureComponent("./assets/r-typesheet30.gif"));
        _registry.add_component<ECS::DestroyableComponent>(e, ECS::DestroyableComponent());
        _registry.add_component<ECS::RectComponent>(e, ECS::RectComponent(ENEMY_RECT_X, ENEMY_RECT_Y, ENEMY_WIDTH, ENEMY_HEIGHT));
        _registry.add_component<ECS::ShootComponent>(e, ECS::ShootComponent());
        _registry.add_component<ECS::LifeComponent>(e, ECS::LifeComponent());
        _registry.add_component<ECS::ComputerComponent>(e, ECS::ComputerComponent());
        Info inf(std::type_index(typeid(ECS::PositionComponent)), e, ECS::PositionComponent(posX, posY, ENEMY_WIDTH, ENEMY_HEIGHT));
        list.push_back(inf);
        Info inf2(std::type_index(typeid(ECS::TextureComponent)), e, ECS::TextureComponent("./assets/r-typesheet30.gif"));
        list.push_back(inf2);
        Info inf3(std::type_index(typeid(ECS::RectComponent)), e, ECS::RectComponent(ENEMY_RECT_X, ENEMY_RECT_Y, ENEMY_WIDTH, ENEMY_HEIGHT));
        list.push_back(inf3);
        Info inf4(std::type_index(typeid(ECS::DestroyableComponent)), e, ECS::DestroyableComponent());
        list.push_back(inf4);
        Info inf5(std::type_index(typeid(ECS::ShootComponent)), e, ECS::ShootComponent());
        list.push_back(inf5);
        Info inf6(std::type_index(typeid(ECS::LifeComponent)), e, ECS::LifeComponent());
        list.push_back(inf6);
        Info inf7(std::type_index(typeid(ECS::ComputerComponent)), e, ECS::ComputerComponent());
        list.push_back(inf7);
    return list;
}
