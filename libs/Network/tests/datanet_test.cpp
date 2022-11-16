/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** hello_test.c
*/

#include <gtest/gtest.h>
#include <DataNet.hpp>

// Demonstrate some basic assertions.
TEST(DataNet, Initialization) {

    DataNet data(5, typeid(int), int(8));

    // Expect equality.
    EXPECT_EQ(data._value, 5);
}

// Demonstrate some basic assertions.
TEST(DataNet, AnyCast) {

    DataNet data(5, typeid(int), int(8));

    // Expect equality.
    EXPECT_EQ(std::any_cast<int>(data._any), 8);
}