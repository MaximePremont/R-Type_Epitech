/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Entity
*/

#include <gtest/gtest.h>
#include "Registry.hpp"

TEST(registry, register_component) {
    ECS::Registry registry;
    ECS::SparseArray<int> & array = registry.register_component<int>();
    array.insert(0);
    EXPECT_EQ(registry.get_components<int>().size(), 1);
}

TEST(registry, spawn_entity) {
    ECS::Registry registry;
    registry.register_component<int>();
    registry.spawn_entity();
    EXPECT_EQ(registry.get_components<int>().size(), 1);
}

TEST(registry, kill_entity) {
    ECS::Registry registry;
    registry.register_component<int>();
    ECS::Entity entity = registry.spawn_entity();
    registry.kill_entity(entity);
    EXPECT_EQ(registry.get_components<int>()[entity], std::nullopt);
}

TEST(registry, add_component) {
    ECS::Registry registry;
    registry.register_component<int>();
    ECS::Entity entity = registry.spawn_entity();
    registry.add_component<int>(entity, 5);
    EXPECT_EQ(registry.get_components<int>()[entity], 5);
}

TEST(registry, remove_component) {
    ECS::Registry registry;
    registry.register_component<int>();
    ECS::Entity entity = registry.spawn_entity();
    registry.add_component<int>(entity, 5);
    registry.remove_component<int>(entity);
    EXPECT_EQ(registry.get_components<int>()[entity], std::nullopt);
}