/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TextureComponent
*/

#pragma once

#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_free.hpp>

namespace ECS {
    class TextureComponent {
        public:
            TextureComponent(std::string const path);

            std::string getPath() const;
            void setPath(std::string const path);

            template <class Archive>
            void save(Archive & ar, const unsigned int version) const {
                (void) version;
                ar & _path;
            }
            template <class Archive>
            void load(Archive & ar, const unsigned int version) {
                (void) version;
                ar & _path;
            }
            BOOST_SERIALIZATION_SPLIT_MEMBER()
        private:
            std::string _path;
    };
}
