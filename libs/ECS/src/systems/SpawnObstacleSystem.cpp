/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SpawnDesObst
*/

#include "SpawnObstacleSystem.hpp"

#include "PositionComponent.hpp"
#include "RectComponent.hpp"
#include "TextureComponent.hpp"
#include "ObstacleComponent.hpp"

#include <stdlib.h>

using namespace ECS;

#define OBSTACLE_WIDTH 256
#define OBSTACLE_HEIGHT 140
#define RECT_OBSTACLE_X 2
#define RECT_OBSTACLE_Y 2

SpawnObstacleSystem::SpawnObstacleSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<ECS::Info> SpawnObstacleSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;
        srand (time(NULL));
        int posX = WINDOW_WIDTH;
        int posY = WINDOW_HEIGHT - OBSTACLE_HEIGHT;

        Entity e = _registry.spawn_entity();
        _registry.add_component<ECS::PositionComponent>(e, ECS::PositionComponent(posX, posY, OBSTACLE_WIDTH, OBSTACLE_HEIGHT));
        _registry.add_component<ECS::TextureComponent>(e, ECS::TextureComponent("./assets/r-typesheet32.gif"));
        _registry.add_component<ECS::RectComponent>(e, ECS::RectComponent(RECT_OBSTACLE_X, RECT_OBSTACLE_Y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT));
        _registry.add_component<ECS::ObstacleComponent>(e, ECS::ObstacleComponent());
        Info inf(std::type_index(typeid(ECS::PositionComponent)), e, ECS::PositionComponent(posX, posY, OBSTACLE_WIDTH, OBSTACLE_HEIGHT));
        list.push_back(inf);
        Info inf2(std::type_index(typeid(ECS::TextureComponent)), e, ECS::TextureComponent("./assets/r-typesheet32.gif"));
        list.push_back(inf2);
        Info inf3(std::type_index(typeid(ECS::RectComponent)), e, ECS::RectComponent(RECT_OBSTACLE_X, RECT_OBSTACLE_Y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT));
        list.push_back(inf3);
        Info inf5(std::type_index(typeid(ECS::ObstacleComponent)), e, ECS::ObstacleComponent());
        list.push_back(inf5);
    return list;
}
