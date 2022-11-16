/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** EnMvmtComponent.cpp
*/

#include "EnMvmtComponent.hpp"

using namespace ECS;

EnMvmtComponent::EnMvmtComponent(int const speed) :
    _speed(speed)
{}

void EnMvmtComponent::setSpeed(int const speed) {
    _speed = speed;
}

int EnMvmtComponent::getSpeed() const {
    return _speed;
}
