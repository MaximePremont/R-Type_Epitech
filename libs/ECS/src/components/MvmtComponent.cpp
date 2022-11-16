/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** MvmtComponent.cpp
*/

#include "MvmtComponent.hpp"

using namespace ECS;

MvmtComponent::MvmtComponent(int const speed) :
    _speed(speed)
{}

void MvmtComponent::setSpeed(int const speed) {
    _speed = speed;
}

int MvmtComponent::getSpeed() const {
    return _speed;
}
