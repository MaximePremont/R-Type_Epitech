/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CoordsComponent
*/

#include "CoordsComponent.hpp"

using namespace ECS;

CoordsComponent::CoordsComponent(int const x, int const y, int const w, int const h) :
    _x(x),
    _y(y),
    _w(w),
    _h(h)
{}

CoordsComponent::CoordsComponent(CoordsComponent const &copy)
{
    _x = copy.getX();
    _y = copy.getY();
    _w = copy.getW();
    _h = copy.getH();
}

void CoordsComponent::setX(int const x) {
    _x = x;
}

void CoordsComponent::setY(int const y) {
    _y = y;
}

void CoordsComponent::setW(int const w) {
    _w = w;
}

void CoordsComponent::setH(int const h) {
    _h = h;
}

int CoordsComponent::getX() const {
    return _x;
}

int CoordsComponent::getY() const {
    return _y;
}

int CoordsComponent::getW() const {
    return _w;
}

int CoordsComponent::getH() const {
    return _h;
}
