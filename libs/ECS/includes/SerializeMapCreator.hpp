/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SerializeMapCreator
*/

#pragma once

#include <unordered_map>
#include <any>
#include <typeindex>

namespace ECS {
    class SerializeMapCreator {
        public:
            typedef void(*SEF)(std::any &, std::any &);

            template <class Archive>
            static std::unordered_map<std::type_index, SEF> & getSerializeMap() {
                if (_serialize.size() > 0)
                    return _serialize;
                _serialize.insert(std::pair<std::type_index, SEF>(std::type_index(typeid(int)), &SerializeMapCreator::int_serialize<Archive>));
            }

            template <class Archive>
            static std::unordered_map<std::type_index, SEF> & getDeserializeMap() {
                if (_deserialize.size() > 0)
                    return _deserialize;
                _deserialize.insert(std::pair<std::type_index, SEF>(std::type_index(typeid(int)), &SerializeMapCreator::int_deserialize<Archive>));
            }
        private:
            static std::unordered_map<std::type_index, SEF> _serialize;
            static std::unordered_map<std::type_index, SEF> _deserialize;

            template <class Archive>
            static void int_serialize(std:: any & anr, std::any & any) {
                Archive & archive = std::any_cast<Archive &>(anr);
                int lan = std::any_cast<int>(any);
                archive & (lan);
            }
            template <class Archive>
            static void int_deserialize(std:: any & anr, std::any & any) {
                Archive & archive = std::any_cast<Archive &>(anr);
                int lan;
                archive &(lan);
                any = std::any(lan);
            }
    };
}
