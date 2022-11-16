/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Registry
*/

#include "Registry.hpp"
#include "SerializeMapCreator.hpp"

#include "PositionComponent.hpp"
#include "TextureComponent.hpp"
#include "RectComponent.hpp"
#include "MvmtComponent.hpp"

using namespace ECS;

Registry::Registry() :
    _number_entities(0),
    _number_users(0)
{}

Entity Registry::spawn_entity() {
    Entity entity(_number_entities);
    for (auto const &[key, val] : _add_empty_functions)
        val(*this);
    _number_entities++;
    return entity;
}

void Registry::kill_entity(Entity const & entity) {
    for (auto const &[key, val] : _remove_functions)
        val(*this, entity);
}

void Registry::add_component(Entity const & entity, std::type_index const tidx, std::any component) {
    std::function<void (Registry &, Entity const &, std::any)> & f = _add_functions[tidx];
    f(*this, entity, component);
}

std::vector<Info> Registry::getConnectComponents() {
    std::vector<Info> map;

    std::vector<Info> posmap = getConComp<PositionComponent>();
    for (size_t i = 0; i < posmap.size(); i++)
        map.push_back(posmap[i]);
    std::vector<Info> texmap = getConComp<TextureComponent>();
    for (size_t i = 0; i < texmap.size(); i++)
        map.push_back(texmap[i]);
    std::vector<Info> recmap = getConComp<RectComponent>();
    for (size_t i = 0; i < recmap.size(); i++)
        map.push_back(recmap[i]);
    MvmtComponent comp;
    Info inf(std::type_index(typeid(MvmtComponent)), _number_users, comp);
    map.push_back(inf);
    _number_users++;
    return map;
}

int Registry::getNumberUsers() const
{
    return _number_users;
}
