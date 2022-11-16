/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** System
*/

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include <cstddef>
#include <optional>
#include <utility>
#include <stdexcept>

#include "Registry.hpp"
#include "Info.hpp"

namespace ECS {
    class Registry;
    class System {
        public:
            /**
             * Call system function
             * 
             * @param params All parameters specific to the system call
             */
            virtual std::vector<Info> callSystem(std::vector<std::any> & params) {
                (void) params;
                throw std::runtime_error("Don't use parent function.");
            }
        private:
            //Registry & _registry;
            // std::optional<std::function<#>>
    };
}

#endif
