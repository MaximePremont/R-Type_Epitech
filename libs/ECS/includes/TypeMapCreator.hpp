/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TypeMapCreator
*/

#pragma once

#include <typeindex>
#include <unordered_map>
#include <string>

namespace ECS {
    class TypeMapCreator {
        public:
            TypeMapCreator();
            std::unordered_map<std::type_index, std::string> & getTypeIndexMap();
        private:
            static std::unordered_map<std::type_index, std::string> _map;
    };
}
