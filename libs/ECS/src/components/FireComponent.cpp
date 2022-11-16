/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** FireComponent
*/

#include "FireComponent.hpp"

using namespace ECS;

FireComponent::FireComponent(int const speed) :
    _speed(speed)
{}

int FireComponent::getSpeed() const {
    return _speed;
}

void FireComponent::setSpeed(int const speed) {
    _speed = speed;
}
