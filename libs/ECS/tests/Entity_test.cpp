/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Entity
*/

#include <gtest/gtest.h>
#include "Entity.hpp"

TEST(entity, explicit_creation) {
    bool error = false;
    try {
        ECS::Entity entity(0);
    } catch(const std::exception& e) {
        error = true;
    }
    EXPECT_EQ(error, false);
}

TEST(entity, conversion) {
    ECS::Entity entity(5);
    EXPECT_EQ(entity, 5);
}