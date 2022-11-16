//
// Created by mikael-vallenet on 18/10/22.
//

#include <gtest/gtest.h>
#include <Network.hpp>

// Demonstrate some basic assertions.
TEST(Network, binarizeCode) {

    int data = 12;
    unsigned char code = binarize_code(data);

    // Expect equality.
    EXPECT_EQ(code, 130);
}