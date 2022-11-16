/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DataNet
*/


#ifndef B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_DATANET_HPP
#define B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_DATANET_HPP

#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_free.hpp>

#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <memory>
#include <any>
#include <vector>

#include "CastMap.hpp"

class DataNet {
    public:
        DataNet(int value, std::type_index idx, std::any any);

        template<class Archive>
        void save(Archive & ar, const unsigned int version) const
        {
            (void) version;
            // note, version is always the latest when saving
            ar & _value;
            ar & _index;
            std::any any_copy(_any);
            CastMap<Archive> map(true);
            std::function<void(Archive &, std::any &)> &f = map[_index];
            f(ar, any_copy);
        }
        template<class Archive>
        void load(Archive & ar, const unsigned int version)
        {
            (void) version;
            ar & _value;
            ar & _index;
            CastMap<Archive> map(false);
            std::function<void(Archive &, std::any &)> &f = map[_index];
            f(ar, _any);
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

        int _value;
        std::type_index _index;
        std::any _any;
        static std::unordered_map<std::type_index, std::string> & _type_map;
        static void registerMapTypes(std::unordered_map<std::type_index, std::string> & map);

        DataNet(DataNet const &d) :
            _value(d._value),
            _index(d._index)
        {
            try {
                _any = d._any;
            } catch(const std::exception& e) {
                (void) e;
            }
        }
        DataNet(DataNet &d) :
            _value(d._value),
            _index(d._index)
        {
            try {
                 _any = d._any;
            } catch(const std::exception& e) {
                (void) e;
            }
        }
};

namespace boost::serialization {
    template<class Archive>
    void save(Archive & ar, const std::type_index & t, unsigned int version)
    {
        (void) version;
        ar << DataNet::_type_map[t];
    }

    template<class Archive>
    void load(Archive & ar, std::type_index & t, unsigned int version) {
        (void) version;
        std::string s = "";
        ar >> s;
        for (auto const &[key, val] : DataNet::_type_map) {
            if (s.compare(val) == 0) {
                t = key;
                break;
            }
        }
    }
}

BOOST_SERIALIZATION_SPLIT_FREE(std::type_index);

#endif  // B_CPP_500_LYN_5_1_RTYPE_MAXIME_PREMONT_DATANET_HPP
