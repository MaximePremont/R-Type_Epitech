/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** FireComponent
*/

#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_free.hpp>

namespace ECS {
    class FireComponent {
        public:
            FireComponent(int const speed = 5);
            
            int getSpeed() const;
            void setSpeed(int const speed);

            template <class Archive>
            void save(Archive & ar, const unsigned int version) const {
                (void) version;
                ar & _speed;
            }
            template <class Archive>
            void load(Archive & ar, const unsigned int version) {
                (void) version;
                ar & _speed;
            }
            BOOST_SERIALIZATION_SPLIT_MEMBER()
        private:
            int _speed;
    };
}
