#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>

class BinaryCodeWord {
public:
    // Construct a binary codeword of given length, initialized to zeros.
    explicit BinaryCodeWord(int length);

    // Rule of 5 (needed because we manage a dynamic int[])
    BinaryCodeWord(const BinaryCodeWord& other);
    BinaryCodeWord(BinaryCodeWord&& other) noexcept;
    BinaryCodeWord& operator=(const BinaryCodeWord& other);
    BinaryCodeWord& operator=(BinaryCodeWord&& other) noexcept;
    ~BinaryCodeWord() = default;

    // Accessors
    int length() const noexcept { return m_length; }

    // Set/get a bit at position [0, length-1]. Values are normalized to {0,1}.
    void setBit(int position, int value);
    int getBit(int position) const;

    // Component-wise XOR
    friend BinaryCodeWord operator+(const BinaryCodeWord& a, const BinaryCodeWord& b);
    BinaryCodeWord& operator+=(const BinaryCodeWord& rhs);

    // Equality
    bool operator==(const BinaryCodeWord& rhs) const noexcept;
    bool operator!=(const BinaryCodeWord& rhs) const noexcept { return !(*this == rhs); }

private:
    int m_length{0};
    std::unique_ptr<int[]> m_bits;

    void requireValidLength(int length) const;
    void requireValidPosition(int position) const;
};
