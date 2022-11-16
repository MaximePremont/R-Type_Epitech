/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** System_test
*/

#include <gtest/gtest.h>
#include "Registry.hpp"

TEST(system, register_system) {
    bool error = false;
    try {
        ECS::Registry registry;
        ECS::System *system = new ECS::System;
        registry.register_system<ECS::System>(system, std::type_index(typeid(system)));
        delete system;
    } catch(const std::exception& e) {
        error = true;
    }
    EXPECT_EQ(error, false);
}

TEST(system, call_system_template) {
    bool error = false;
    ECS::Registry registry;
    ECS::System *system = new ECS::System;
    registry.register_system<ECS::System>(system, std::type_index(typeid(system)));
    std::vector<std::any> params;
    try {
        registry.call_system(std::type_index(typeid(ECS::System)), params);
    } catch(const std::exception& e) {
        error = true;
    }
    delete system;
    EXPECT_EQ(error, true);
}

TEST(system, call_system_type) {
    bool error = false;
    ECS::Registry registry;
    ECS::System *system = new ECS::System;
    registry.register_system<ECS::System>(system, std::type_index(typeid(system)));
    std::vector<std::any> params;
    try {
        registry.call_system(std::type_index(typeid(ECS::System)), params);
    } catch(const std::exception& e) {
        error = true;
    }
    delete system;
    EXPECT_EQ(error, true);
}
