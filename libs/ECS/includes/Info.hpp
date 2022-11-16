/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Info
*/

#pragma once

#include <cstddef>
#include <any>
#include <typeindex>

namespace ECS {
    class Info {
        public:
            Info(std::type_index, std::size_t, std::any);
            std::type_index _index;
            std::size_t _value;
            std::any _any;
    };
}