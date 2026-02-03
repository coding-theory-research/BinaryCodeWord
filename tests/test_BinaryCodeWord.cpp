#include <gtest/gtest.h>
#include "BinaryCodeWord/BinaryCodeWord.hpp"

TEST(BinaryCodeWord, InitializesToZero) {
    BinaryCodeWord w(5);
    for (int i = 0; i < w.length(); ++i) {
        EXPECT_EQ(w.getBit(i), 0);
    }
}

TEST(BinaryCodeWord, SetAndGetBit) {
    BinaryCodeWord w(4);
    w.setBit(2, 1);
    EXPECT_EQ(w.getBit(2), 1);

    w.setBit(2, 7); // normalized to 1
    EXPECT_EQ(w.getBit(2), 1);

    w.setBit(2, 0);
    EXPECT_EQ(w.getBit(2), 0);
}

TEST(BinaryCodeWord, PlusIsXor) {
    BinaryCodeWord a(4), b(4);
    a.setBit(0, 1);
    a.setBit(2, 1);

    b.setBit(2, 1);
    b.setBit(3, 1);

    BinaryCodeWord c = a + b;

    EXPECT_EQ(c.getBit(0), 1);
    EXPECT_EQ(c.getBit(1), 0);
    EXPECT_EQ(c.getBit(2), 0);
    EXPECT_EQ(c.getBit(3), 1);
}

TEST(BinaryCodeWord, PlusEqualsChains) {
    BinaryCodeWord a(4), b(4), c(4);
    a.setBit(1, 1);
    b.setBit(1, 1);
    c.setBit(2, 1);

    a += b; // cancels bit 1
    EXPECT_EQ(a.getBit(1), 0);

    a += c; // sets bit 2
    EXPECT_EQ(a.getBit(2), 1);
}

TEST(BinaryCodeWord, Equality) {
    BinaryCodeWord a(3), b(3);
    EXPECT_TRUE(a == b);
    a.setBit(0, 1);
    EXPECT_TRUE(a != b);
    b.setBit(0, 1);
    EXPECT_TRUE(a == b);
}

TEST(BinaryCodeWord, LengthMismatchThrows) {
    BinaryCodeWord a(3), b(4);
    EXPECT_THROW((void)(a + b), std::invalid_argument);
    EXPECT_THROW(a += b, std::invalid_argument);
}
