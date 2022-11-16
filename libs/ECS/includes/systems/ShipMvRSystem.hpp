/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ShipMvRSystem
*/

#pragma once

#include "Registry.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_free.hpp>

namespace ECS {
    class ShipMvRSystem : public ECS::System {
        public:
            ShipMvRSystem(ECS::Registry & registry);
            std::vector<Info> callSystem(std::vector<std::any> & params) override;

        private:
            ECS::Registry & _registry;
    };  
}
