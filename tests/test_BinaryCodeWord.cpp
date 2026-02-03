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

TEST(BinaryCodeWord, PositionOutOfBoundsThrows) {
    BinaryCodeWord w(3);
    EXPECT_THROW(w.setBit(-1, 1), std::out_of_range);
    EXPECT_THROW(w.setBit(3, 1), std::out_of_range);
    EXPECT_THROW(w.getBit(-1), std::out_of_range);
    EXPECT_THROW(w.getBit(3), std::out_of_range);
}

TEST(BinaryCodeWord, CopyConstructor) {
    BinaryCodeWord a(4);
    a.setBit(1, 1);
    BinaryCodeWord b = a; // copy constructor
    EXPECT_EQ(b.length(), 4);
    EXPECT_EQ(b.getBit(1), 1);
    EXPECT_EQ(b.getBit(0), 0);
}

TEST(BinaryCodeWord, MoveConstructor) {
    BinaryCodeWord a(4);
    a.setBit(2, 1);
    BinaryCodeWord b = std::move(a); // move constructor
    EXPECT_EQ(b.length(), 4);
    EXPECT_EQ(b.getBit(2), 1);
}

TEST(BinaryCodeWord, CopyAssignment) {
    BinaryCodeWord a(4);
    a.setBit(0, 1);
    BinaryCodeWord b(4);
    b = a; // copy assignment
    EXPECT_EQ(b.length(), 4);
    EXPECT_EQ(b.getBit(0), 1);
    EXPECT_EQ(b.getBit(1), 0);
}

TEST(BinaryCodeWord, MoveAssignment) {
    BinaryCodeWord a(4);
    a.setBit(3, 1);
    BinaryCodeWord b(4);
    b = std::move(a); // move assignment
    EXPECT_EQ(b.length(), 4);
    EXPECT_EQ(b.getBit(3), 1);
}

TEST(BinaryCodeWord, OutputStream) {
    BinaryCodeWord w(3);
    w.setBit(0, 1);
    w.setBit(2, 1);
    std::ostringstream oss;
    oss << w;
    EXPECT_EQ(oss.str(), "(101)");
}

TEST(BinaryCodeWord, IsZero) {
    BinaryCodeWord w(3);
    EXPECT_TRUE(w.isZero());
    w.setBit(1, 1);
    EXPECT_FALSE(w.isZero());
    w.setBit(1, 0);
    EXPECT_TRUE(w.isZero());
}

TEST(BinaryCodeWord, Reset) {
    BinaryCodeWord w(3);
    w.setBit(0, 1);
    w.reset(5);
    EXPECT_EQ(w.length(), 5);
    for (int i = 0; i < w.length(); ++i) {
        EXPECT_EQ(w.getBit(i), 0);
    }
}

TEST(BinaryCodeWord, UninitializedThrows) {
    BinaryCodeWord w;
    EXPECT_THROW(w.getBit(0), std::runtime_error);
    EXPECT_THROW(w.setBit(0, 1), std::runtime_error);
    EXPECT_THROW(w.isZero(), std::runtime_error);
    // EXPECT_THROW((void)(w + w), std::runtime_error);
    // EXPECT_THROW(w += w, std::runtime_error);
    // // EXPECT_THROW(w == w, std::runtime_error);
    // std::ostringstream oss;
    // EXPECT_THROW(oss << w, std::runtime_error);
}

TEST(BinaryCodeWord, LargeCodeWord) {
    const int length = 1000;
    BinaryCodeWord w(length);
    for (int i = 0; i < length; i += 2) {
        w.setBit(i, 1);
    }
    for (int i = 0; i < length; ++i) {
        EXPECT_EQ(w.getBit(i), (i % 2 == 0) ? 1 : 0);
    }
}

TEST(BinaryCodeWord, DefaultConstructor) {
    BinaryCodeWord w;
    EXPECT_FALSE(w.initialized());
    EXPECT_THROW(w.getBit(0), std::runtime_error);
    EXPECT_THROW(w.setBit(0, 1), std::runtime_error);
    EXPECT_THROW(w.isZero(), std::runtime_error);
}
