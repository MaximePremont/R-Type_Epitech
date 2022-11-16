/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** TripleShotComp.hpp
*/

#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_free.hpp>

namespace ECS {
    class TripleShotComp {
        public:
            TripleShotComp(time_t startTime = time(0));
            time_t getStartTime() const;

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

        private:
            time_t _startTime;
    };
}