/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PositionComponent
*/

#include "PositionComponent.hpp"

using namespace ECS;

PositionComponent::PositionComponent(int const x, int const y, int const w, int const h) :
    CoordsComponent(x, y, w, h)
{}

PositionComponent::PositionComponent(PositionComponent const &copy)
{
    _x = copy.getX();
    _y = copy.getY();
    _w = copy.getW();
    _h = copy.getH();
}
