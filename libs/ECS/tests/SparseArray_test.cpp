/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Sparse_array_test
*/

#include <gtest/gtest.h>
#include "SparseArray.hpp"

TEST(sparse_array, basic_insertion) {
    ECS::SparseArray<int> array;

    array.insert(5);
    EXPECT_EQ(array[0], 5);
}

TEST(sparse_array, size) {
    ECS::SparseArray<int> array;

    array.insert(5);
    array.insert(8);
    EXPECT_EQ(array.size(), 2);
}

TEST(sparse_array, erase) {
    ECS::SparseArray<int> array;

    array.insert(5);
    array.erase(0);
    array.insert(8);
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], std::nullopt);
}

TEST(sparse_array, iterator_begin) {
    ECS::SparseArray<int> array;
    bool error = false;
    try {
        array.iterator_begin();
        array.const_iterator_begin();
    } catch(const std::exception& e) {
        error = true;
    }
    EXPECT_EQ(error, false);
}

TEST(sparse_array, iterator_end) {
    ECS::SparseArray<int> array;
    bool error = false;
    try {
        array.iterator_end();
        array.const_iterator_end();
    } catch(const std::exception& e) {
        error = true;
    }
    EXPECT_EQ(error, false);
}
