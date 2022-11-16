/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** EnMvmtComponent.hpp
*/

#pragma once

#define DEFAULT_SPEED 10

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_free.hpp>

namespace ECS {
    class EnMvmtComponent {
        public:
            EnMvmtComponent(int const speed = DEFAULT_SPEED);

            void setSpeed(int const speed);
            int getSpeed() const;

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
