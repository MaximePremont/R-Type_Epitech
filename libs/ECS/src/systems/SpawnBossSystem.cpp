/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SpawnBoss
*/

#include "SpawnBossSystem.hpp"

#include "PositionComponent.hpp"
#include "RectComponent.hpp"
#include "TextureComponent.hpp"
#include "DestroyableComponent.hpp"
#include "ShootComponent.hpp"
#include "LazerComponent.hpp"
#include "LifeComponent.hpp"
#include "ComputerComponent.hpp"
#include "EnMvmtComponent.hpp"

#include <stdlib.h>

#define BOSS_WIDTH 128
#define BOSS_HEIGHT 128
#define RECT_BOSS_X 67
#define RECT_BOSS_Y 34
#define BOSS_LIVES  5
#define BOSS_SPEED  3

using namespace ECS;

SpawnBossSystem::SpawnBossSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<ECS::Info> SpawnBossSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;
        srand (time(NULL));
        int posX = WINDOW_WIDTH - BOSS_WIDTH;
        int posY = rand() % (WINDOW_HEIGHT - BOSS_HEIGHT) + 0;

        Entity e = _registry.spawn_entity();
        _registry.add_component<ECS::PositionComponent>(e, ECS::PositionComponent(posX, posY, BOSS_WIDTH, BOSS_HEIGHT));
        _registry.add_component<ECS::TextureComponent>(e, ECS::TextureComponent("./assets/r-typesheet7.gif"));
        _registry.add_component<ECS::DestroyableComponent>(e, ECS::DestroyableComponent());
        _registry.add_component<ECS::RectComponent>(e, ECS::RectComponent(RECT_BOSS_X, RECT_BOSS_Y, 32, 32));
        _registry.add_component<ECS::ShootComponent>(e, ECS::ShootComponent());
        _registry.add_component<ECS::LifeComponent>(e, ECS::LifeComponent(BOSS_LIVES));
        _registry.add_component<ECS::ComputerComponent>(e, ECS::ComputerComponent());
        _registry.add_component<ECS::LazerComponent>(e, ECS::LazerComponent());
        _registry.add_component<ECS::EnMvmtComponent>(e, ECS::EnMvmtComponent(BOSS_SPEED));
        Info inf(std::type_index(typeid(ECS::PositionComponent)), e, ECS::PositionComponent(posX, posY, BOSS_WIDTH, BOSS_HEIGHT));
        list.push_back(inf);
        Info inf2(std::type_index(typeid(ECS::TextureComponent)), e, ECS::TextureComponent("./assets/r-typesheet7.gif"));
        list.push_back(inf2);
        Info inf3(std::type_index(typeid(ECS::RectComponent)), e, ECS::RectComponent(RECT_BOSS_X, RECT_BOSS_Y, 32, 32));
        list.push_back(inf3);
        Info inf4(std::type_index(typeid(ECS::DestroyableComponent)), e, ECS::DestroyableComponent());
        list.push_back(inf4);
        Info inf5(std::type_index(typeid(ECS::ShootComponent)), e, ECS::ShootComponent());
        list.push_back(inf5);
        Info inf6(std::type_index(typeid(ECS::LifeComponent)), e, ECS::LifeComponent(BOSS_LIVES));
        list.push_back(inf6);
        Info inf7(std::type_index(typeid(ECS::ComputerComponent)), e, ECS::ComputerComponent());
        list.push_back(inf7);
        Info inf8(std::type_index(typeid(ECS::LazerComponent)), e, ECS::LazerComponent());
        list.push_back(inf8);
        Info inf9(std::type_index(typeid(ECS::EnMvmtComponent)), e, ECS::EnMvmtComponent(BOSS_SPEED));
        list.push_back(inf9);
    return list;
}
