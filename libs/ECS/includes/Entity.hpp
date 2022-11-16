/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Entity
*/

#pragma once

#include <cstddef>

namespace ECS {
    class Entity {
        public:
            /**
             * Entity constructor
             * 
             * This function only need to be called by the registry, please
             * use Registry.spawn_entity() for new entities.
             * 
             * @param id Entity id in components map
             * @return Entity instantiation
             */
            explicit Entity(const std::size_t id);
            /**
             * Entity conversion
             * 
             * @return Entity id
             */
            operator std::size_t() const;
        private:
            const std::size_t _id;
    };
}
