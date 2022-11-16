/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** LifeComponent
*/

#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_free.hpp>

namespace ECS {
    class LifeComponent {
        public:
            LifeComponent(int const lives = 1);
            
            int getLives() const;
            void setLives(int const lives);

            template <class Archive>
            void save(Archive & ar, const unsigned int version) const {
                (void) version;
                ar & _lives;
            }
            template <class Archive>
            void load(Archive & ar, const unsigned int version) {
                (void) version;
                ar & _lives;
            }
            BOOST_SERIALIZATION_SPLIT_MEMBER()
        private:
            int _lives;
    };
}
