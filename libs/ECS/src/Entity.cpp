/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Entity
*/

#include "Entity.hpp"

using namespace ECS;

Entity::Entity(const std::size_t id) : _id(id) {}

Entity::operator std::size_t() const { return _id; }
