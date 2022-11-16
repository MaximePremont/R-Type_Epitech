/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PositionComponent
*/

#pragma once

#include "CoordsComponent.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_free.hpp>

namespace ECS {
    class PositionComponent : public CoordsComponent {
        public:
            PositionComponent(int const x = 0, int const y = 0, int const w = 1, int const h = 1);
            PositionComponent(PositionComponent const &copy);

            template <class Archive>
            void save(Archive & ar, const unsigned int version) const {
                (void) version;
                ar & _x;
                ar & _y;
                ar & _w;
                ar & _h;
            }
            template <class Archive>
            void load(Archive & ar, const unsigned int version) {
                (void) version;
                ar & _x;
                ar & _y;
                ar & _w;
                ar & _h;
            }
            BOOST_SERIALIZATION_SPLIT_MEMBER()
    };
}
