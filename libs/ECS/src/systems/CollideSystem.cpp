/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** CollideSystem.cpp
*/

#include "CollideSystem.hpp"

#include "ObstacleComponent.hpp"
#include "PositionComponent.hpp"
#include "MvmtComponent.hpp"

using namespace ECS;

CollideSystem::CollideSystem(Registry & registry) :
    _registry(registry)
{}

std::vector<Info> CollideSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;

    auto &positions = _registry.get_components<ECS::PositionComponent>();
    auto const &moving = _registry.get_components<ECS::MvmtComponent>();
    auto const &obstacles = _registry.get_components<ECS::ObstacleComponent>();

    for (int i = 0; i < positions.size() && i < moving.size(); i++) {
        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        auto &player = moving[i];
        auto &playerPos = positions[i];
        if (player && playerPos) {
            for (int j = 0; j < positions.size() && j < obstacles.size(); j++) {
                auto &obstacle = obstacles[j];
                auto &obstaclePos = positions[j];
                if (obstacle && obstaclePos) {
                    auto &vPlayerPos = playerPos.value();
                    auto &vObstaclePos = obstaclePos.value();
                    if ((vPlayerPos.getX() + vPlayerPos.getW())  >= vObstaclePos.getX() && 
                        vPlayerPos.getY() >= vObstaclePos.getY() &&
                        (vPlayerPos.getY() + vPlayerPos.getH()) <= (vObstaclePos.getY() + vObstaclePos.getH()) &&
                        vPlayerPos.getX() <= (vObstaclePos.getX() + vObstaclePos.getW()) &&
                        (vObstaclePos.getX() - 83 > 0)) {
                            vPlayerPos.setX(vObstaclePos.getX() - 83);
                            PositionComponent modPos(vPlayerPos);
                            Info inf(std::type_index(typeid(PositionComponent)), i, modPos);
                            list.push_back(inf);
                    }
                }
            }
        }
    }
    return list;
}
