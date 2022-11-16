/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** MoveObstacleSystem.hpp
*/

#pragma once

#include "Registry.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_free.hpp>

namespace ECS {
    class MoveObstacleSystem : public ECS::System {
        public:
            MoveObstacleSystem(ECS::Registry & registry);
            std::vector<Info> callSystem(std::vector<std::any> & params) override;

        private:
            ECS::Registry & _registry;
    };  
}
