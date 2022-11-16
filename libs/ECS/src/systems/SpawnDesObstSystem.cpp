/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SpawnDesObst
*/

#include "SpawnDesObstSystem.hpp"

#include "PositionComponent.hpp"
#include "RectComponent.hpp"
#include "TextureComponent.hpp"
#include "LifeComponent.hpp"
#include "ComputerComponent.hpp"
#include "ObstacleComponent.hpp"

#include <stdlib.h>

using namespace ECS;

#define OBSTACLE_WIDTH 55
#define OBSTACLE_HEIGHT 23
#define RECT_OBSTACLE_X 315
#define RECT_OBSTACLE_Y 83

SpawnDesObstSystem::SpawnDesObstSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<ECS::Info> SpawnDesObstSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;
        srand (time(NULL));
        int posX = WINDOW_WIDTH;
        int posY = 0;

        Entity e = _registry.spawn_entity();
        _registry.add_component<ECS::PositionComponent>(e, ECS::PositionComponent(posX, posY, OBSTACLE_WIDTH * 2, OBSTACLE_HEIGHT * 2));
        _registry.add_component<ECS::TextureComponent>(e, ECS::TextureComponent("./assets/r-typesheet41.gif"));
        _registry.add_component<ECS::RectComponent>(e, ECS::RectComponent(RECT_OBSTACLE_X, RECT_OBSTACLE_Y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT));
        _registry.add_component<ECS::ObstacleComponent>(e, ECS::ObstacleComponent());
        _registry.add_component<ECS::ComputerComponent>(e, ECS::ComputerComponent());
        _registry.add_component<ECS::LifeComponent>(e, ECS::LifeComponent(1));
        Info inf(std::type_index(typeid(ECS::PositionComponent)), e, ECS::PositionComponent(posX, posY, OBSTACLE_WIDTH * 2, OBSTACLE_HEIGHT * 2));
        list.push_back(inf);
        Info inf2(std::type_index(typeid(ECS::TextureComponent)), e, ECS::TextureComponent("./assets/r-typesheet41.gif"));
        list.push_back(inf2);
        Info inf3(std::type_index(typeid(ECS::RectComponent)), e, ECS::RectComponent(RECT_OBSTACLE_X, RECT_OBSTACLE_Y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT));
        list.push_back(inf3);
        Info inf5(std::type_index(typeid(ECS::ObstacleComponent)), e, ECS::ObstacleComponent());
        list.push_back(inf5);
        Info inf6(std::type_index(typeid(ECS::LifeComponent)), e, ECS::LifeComponent(1));
        list.push_back(inf6);
        Info inf7(std::type_index(typeid(ECS::ComputerComponent)), e, ECS::ComputerComponent());
        list.push_back(inf7);
    return list;
}
