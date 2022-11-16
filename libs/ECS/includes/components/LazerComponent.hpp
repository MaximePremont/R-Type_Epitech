/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** LazerComponent
*/

#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_free.hpp>

namespace ECS {
    class LazerComponent {
        public:
            LazerComponent();

            template <class Archive>
            void save(Archive & ar, const unsigned int version) const {
                (void) version;
                (void) ar;
            }
            template <class Archive>
            void load(Archive & ar, const unsigned int version) {
                (void) version;
                (void) ar;
            }
            BOOST_SERIALIZATION_SPLIT_MEMBER()
    };
}
