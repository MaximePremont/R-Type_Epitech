/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DataNet
*/

#include "DataNet.hpp"

#include <utility>

std::unordered_map<std::type_index, std::string> usableMap;
std::unordered_map<std::type_index, std::string> & DataNet::_type_map = usableMap;

/**
 * DataNet constructor
 * 
 * The DataNet is the object which contains data to transmit
 * 
 * @param value a integer value
 * @param idx the type of the any var
 * @param any any object to transmit
 */
DataNet::DataNet(int value, std::type_index idx, std::any any) :
    _value(value),
    _index(idx)
{
    try {
        _any = any;
    } catch(const std::exception& e) {
        (void) e;
    }
}

/**
 * Register the map which contains all type
 * 
 * @param map map is collection that contains {std::type_index} as key and {std::string} as value
 */
void DataNet::registerMapTypes(std::unordered_map<std::type_index, std::string> & map) {
    _type_map = map;
}
