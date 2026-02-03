#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>
#include <ostream>

class BinaryCodeWord {
public:
    // Default constructor: uninitialized (length == 0, no storage).
    // Any bit/arith operation should throw until reset(length) is called.
    BinaryCodeWord() noexcept = default;

    // Construct initialized codeword of given length (all zeros)
    explicit BinaryCodeWord(int length);

    // Rule of 5
    BinaryCodeWord(const BinaryCodeWord& other);
    BinaryCodeWord(BinaryCodeWord&& other) noexcept;
    BinaryCodeWord& operator=(const BinaryCodeWord& other);
    BinaryCodeWord& operator=(BinaryCodeWord&& other) noexcept;
    ~BinaryCodeWord() = default;

    // (Re)initialize this object to the given length (all zeros).
    // If already initialized, this discards previous contents.
    void reset(int length);

    bool initialized() const noexcept { return m_length > 0 && m_words != nullptr; }
    void verifyInitialized() const;
    int  length() const noexcept { return m_length; }

    void setBit(int position, int value);
    int  getBit(int position) const;

    // True iff all coordinates are 0 (throws if uninitialized)
    bool isZero() const;
    void swap(int c1, int c2);

    // XOR
    friend BinaryCodeWord operator+(const BinaryCodeWord& a, const BinaryCodeWord& b);
    BinaryCodeWord& operator+=(const BinaryCodeWord& rhs);

    // Equality
    bool operator==(const BinaryCodeWord& rhs) const;
    bool operator!=(const BinaryCodeWord& rhs) const { return !(*this == rhs); }

    // Print as "(0101...)" using bit order 0..length-1
    friend std::ostream& operator<<(std::ostream& os, const BinaryCodeWord& w);

private:
    using word_t = std::uint64_t;
    static constexpr int WORD_BITS = 8 * sizeof(word_t);

    int m_length{0};
    int m_numWords{0};
    std::unique_ptr<word_t[]> m_words;

    static int computeNumWords(int bits) noexcept {
        return (bits + WORD_BITS - 1) / WORD_BITS;
    }

    void requireValidLength(int length) const;
    void requireSized() const;
    void requireValidPosition(int position) const;

    // Mask off unused bits in last word (keeps equality/isZero stable)
    void maskUnusedBits() noexcept;
};
