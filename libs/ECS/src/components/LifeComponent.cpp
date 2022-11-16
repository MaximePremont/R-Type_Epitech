/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** LifeComponent
*/

#include "LifeComponent.hpp"

using namespace ECS;

LifeComponent::LifeComponent(int const lives) :
    _lives(lives)
{}

int LifeComponent::getLives() const {
    return _lives;
}

void LifeComponent::setLives(int const lives) {
    _lives = lives;
}
