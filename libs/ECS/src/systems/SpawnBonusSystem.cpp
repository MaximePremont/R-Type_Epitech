/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** SpawnBonusSystem.cpp
*/

#include "SpawnBonusSystem.hpp"

#include "PositionComponent.hpp"
#include "RectComponent.hpp"
#include "TextureComponent.hpp"
#include "ObtainableComponent.hpp"

#include <stdlib.h>

#define BONUS_WIDTH 16
#define BONUS_HEIGHT 14
#define BONUS_RECT_X 52
#define BONUS_RECT_Y 2


using namespace ECS;

SpawnBonusSystem::SpawnBonusSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<ECS::Info> SpawnBonusSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;
        srand (time(NULL));
        int posX = rand() % (WINDOW_WIDTH / 2) - BONUS_WIDTH;
        int posY = rand() % (WINDOW_HEIGHT - BONUS_HEIGHT) + 0;

        Entity e = _registry.spawn_entity();
        _registry.add_component<ECS::PositionComponent>(e, ECS::PositionComponent(posX, posY, BONUS_WIDTH, BONUS_HEIGHT));
        _registry.add_component<ECS::TextureComponent>(e, ECS::TextureComponent("./assets/r-typesheet3.gif"));
        _registry.add_component<ECS::ObtainableComponent>(e, ECS::ObtainableComponent());
        _registry.add_component<ECS::RectComponent>(e, ECS::RectComponent(BONUS_RECT_X, BONUS_RECT_Y, BONUS_WIDTH, BONUS_HEIGHT));
        Info inf(std::type_index(typeid(ECS::PositionComponent)), e, ECS::PositionComponent(posX, posY, BONUS_WIDTH, BONUS_HEIGHT));
        list.push_back(inf);
        Info inf2(std::type_index(typeid(ECS::TextureComponent)), e, ECS::TextureComponent("./assets/r-typesheet3.gif"));
        list.push_back(inf2);
        Info inf3(std::type_index(typeid(ECS::RectComponent)), e, ECS::RectComponent(BONUS_RECT_X, BONUS_RECT_Y, BONUS_WIDTH, BONUS_HEIGHT));
        list.push_back(inf3);
        Info inf4(std::type_index(typeid(ECS::ObtainableComponent)), e, ECS::ObtainableComponent());
        list.push_back(inf4);
    return list;
}
