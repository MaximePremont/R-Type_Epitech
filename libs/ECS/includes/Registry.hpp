/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Registry
*/

#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

#define SHIP_RIGHT_X 500
#define SHIP_RIGHT_Y 0
#define SHIP_LEFT_X 0
#define SHIP_LEFT_Y 0
#define SHIP_WIDTH 0
#define SHIP_HEIGHT 0
#define ENEMY_WIDTH 180
#define ENEMY_HEIGHT 208
#define ENEMY_RECT_X 0
#define ENEMY_RECT_Y 208

#include <map>
#include <typeindex>
#include <any>
#include <functional>
#include <stdexcept>

#include <iostream>

#include "SparseArray.hpp"
#include "Entity.hpp"

#include "System.hpp"

namespace ECS {
    class System;
    class Registry {
        public:
            Registry();
            /**
             * Component type registration
             * 
             * Register a specific component class/type to be used by entities, this function
             * must be called before entities creation.
             * 
             * @return SparseArray of newly registered component
             */
            template <class Component>
            SparseArray<Component> & register_component() {
                std::type_index idx(typeid(Component));
                _components_arrays.insert(std::pair<std::type_index, std::any>(idx, SparseArray<Component>()));
                std::function<void (Registry &)> add_empty_function = [](Registry & registry) {
                    SparseArray<Component> & array = registry.get_components<Component>();
                    array.insert(std::optional<Component>(std::nullopt));
                };
                _add_empty_functions.insert(std::pair<std::type_index, std::function<void (Registry &)>>(idx, add_empty_function));
                std::function<void (Registry &, Entity const &)> remove_function = [](Registry & registry, Entity const & entity) {
                    SparseArray<Component> & array = registry.get_components<Component>();
                    array.erase(entity);
                };
                _remove_functions.insert(std::pair<std::type_index, std::function<void (Registry &, Entity const &)>>(idx, remove_function));
                std::function<void (Registry &, Entity const &, std::any &&)> add_function = [](Registry & registry, Entity const & entity, std::any component) {
                    SparseArray<Component> & array = registry.get_components<Component>();
                    while (array.size() <= entity)
                        registry.spawn_entity();
                    SparseArray<Component> & carray = registry.get_components<Component>();
                    carray[entity].emplace(std::any_cast<Component>(component));
                };
                _add_functions.insert(std::pair<std::type_index, std::function<void (Registry &, Entity const &, std::any)>>(idx, add_function));
                return std::any_cast<SparseArray<Component>&>(_components_arrays[idx]);
            }

            /**
             * Components list getter
             * 
             * Get the array of components of a specific class/type.
             * 
             * @param component Optional component
             * @return Reference to a SparseArray of components
             */
            template <class Component>
            SparseArray<Component> & get_components() {
                std::type_index const idx(typeid(Component));
                return std::any_cast<SparseArray<Component>&>(_components_arrays[idx]);
            }

            /**
             * Spawn entity
             * 
             * @return Newly created entity
             */
            Entity spawn_entity();
            /**
             * Kill entity
             * 
             * All components associated to this entity will be deleted.
             * 
             * @param Entity to kill
             */
            void kill_entity(Entity const & entity);

            /**
             * Add component to entity
             * 
             * @param Entity The entity defined for component addition
             * @param Component Component to add (will be moved)
             */
            template <class Component>
            void add_component(Entity const & entity, Component component) {
                std::type_index const idx(typeid(Component));
                SparseArray<Component> & array = std::any_cast<SparseArray<Component>&>(_components_arrays[idx]);
                while (array.size() < entity)
                    spawn_entity();
                array[entity].emplace(component);
            }
            /**
             * Remove component to entity
             * 
             * @param Entity The entity defined for component deletion
             */
            template <class Component>
            void remove_component(Entity const & from) {
                std::type_index const idx(typeid(Component));
                SparseArray<Component> & array = std::any_cast<SparseArray<Component>&>(_components_arrays[idx]);
                array.erase(from);
            }

            /**
             * Register new event system
             * 
             * @param system System to register
             * @param idx Type index of the system to register
             */
            template <class SystemT>
            void register_system(SystemT *system, std::type_index const idx) {
                _systems.insert(std::pair<std::type_index, SystemT*>(idx, system));
                std::function<std::vector<Info> (Registry &, std::vector<std::any>)> call_function = [](Registry & registry, std::vector<std::any> params) {
                    return registry.call_system<SystemT>(params);
                };
                _call_functions.insert(std::pair<std::type_index, std::function<std::vector<Info> (Registry &, std::vector<std::any>)>>(idx, call_function));
            }
            /**
             * Call an event system
             * 
             * Usable with template
             * 
             * @param params Call parameters
             * @return List of modified components
             */
            template <class SystemT>
            std::vector<Info> call_system(std::vector<std::any> params) {
                std::type_index const idx(typeid(SystemT));
                //return ((SystemT*) _systems[idx])->callSystem(params);
                SystemT *sys = (SystemT*) _systems[idx];
                return sys->callSystem(params);
            }
            /**
             * Call an event system
             * 
             * @param tidx Type index of system child to call
             * @param params Call parameters
             * @return List of modified components
             */
            std::vector<Info> call_system(std::type_index const tidx, std::vector<std::any> params) {
                std::function<std::vector<Info> (Registry &, std::vector<std::any>)> & func = _call_functions[tidx];
                return func(*this, params);
                //return std::map<std::type_index, std::pair<std::size_t, std::any>>();
            }

            /**
             * Add component to entity
             * 
             * @param entity Entity to add the component
             * @param tidx Type index of component
             * @param component Component to add
             */
            void add_component(Entity const & entity, std::type_index const tidx, std::any component);

            std::vector<Info> getConnectComponents();
            int getNumberUsers() const;
        private:
            std::size_t _number_entities;
            std::map<std::type_index, std::any> _components_arrays;
            std::map<std::type_index, std::function<void (Registry &)>> _add_empty_functions;
            std::map<std::type_index, std::function<void (Registry &, Entity const &)>> _remove_functions;
            std::map<std::type_index, System*> _systems;
            std::map<std::type_index, std::function<void (Registry &, Entity const &, std::any)>> _add_functions;
            std::map<std::type_index, std::function<std::vector<Info> (Registry &, std::vector<std::any>)>> _call_functions;
            std::size_t _number_users;

            template <class Component>
            std::vector<Info> getConComp() {
                std::vector<Info> map;
                SparseArray<Component> &posarr = get_components<Component>();
                for (std::size_t i = 0; i < posarr.size(); i++) {
                    if (posarr[i]) {
                        Component modPos(posarr[i].value());
                        map.push_back(ECS::Info(std::type_index(typeid(Component)), i, modPos));
                    }
                }
                return map;
            }
    };
}

#endif
