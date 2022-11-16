/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Info
*/

#include "Info.hpp"

using namespace ECS;

Info::Info(std::type_index index, std::size_t value, std::any any) :
    _index(index),
    _value(value),
    _any(any)
{}
