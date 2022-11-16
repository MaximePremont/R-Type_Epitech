/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** MoveObstacleSystem.cpp
*/

#include "MoveObstacleSystem.hpp"
#include "MvmtComponent.hpp"
#include "PositionComponent.hpp"
#include "ObstacleComponent.hpp"
#include "IgnoreComponent.hpp"

#define OBSTACLE_SPEED -1

using namespace ECS;

MoveObstacleSystem::MoveObstacleSystem(ECS::Registry & registry) :
    _registry(registry)
{}

std::vector<Info> MoveObstacleSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;

    auto &positions = _registry.get_components<ECS::PositionComponent>();
    auto const &obstacles = _registry.get_components<ECS::ObstacleComponent>();

    for (int i = 0; i < positions.size() && i < obstacles.size(); i++) {
        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        
        auto &pos = positions[i];
        auto const &obstacle = obstacles[i];

        if (pos && obstacle) {
            auto &vpos = pos.value();
            auto const &vObstacle= obstacle.value();
            vpos.setX(vpos.getX() + OBSTACLE_SPEED);
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
