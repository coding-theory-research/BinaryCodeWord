#ifndef BINARY_CODE_WORD_HPP
#define BINARY_CODE_WORD_HPP

#include <cstdint>
#include <cstddef>
#include <memory>
#include <ostream>
#include <stdexcept>

class BinaryCodeWord {
public:
    explicit BinaryCodeWord(int length);

    // Rule of 5
    BinaryCodeWord(const BinaryCodeWord& other);
    BinaryCodeWord(BinaryCodeWord&& other) noexcept;
    BinaryCodeWord& operator=(const BinaryCodeWord& other);
    BinaryCodeWord& operator=(BinaryCodeWord&& other) noexcept;
    ~BinaryCodeWord() = default;

    int length() const noexcept { return m_length; }

    void setBit(int position, int value);
    int  getBit(int position) const;

    bool isZero() const noexcept;

    // XOR
    friend BinaryCodeWord operator+(const BinaryCodeWord& a,
                                    const BinaryCodeWord& b);
    BinaryCodeWord& operator+=(const BinaryCodeWord& rhs);

    // Equality
    bool operator==(const BinaryCodeWord& rhs) const noexcept;
    bool operator!=(const BinaryCodeWord& rhs) const noexcept {
        return !(*this == rhs);
    }

    // Printing
    friend std::ostream& operator<<(std::ostream& os,
                                    const BinaryCodeWord& w);

private:
    using word_t = std::uint64_t;
    static constexpr int WORD_BITS = 8 * sizeof(word_t);

    int m_length{0};
    int m_numWords{0};
    std::unique_ptr<word_t[]> m_words;

    static int computeNumWords(int bits) noexcept {
        return (bits + WORD_BITS - 1) / WORD_BITS;
    }

    void maskUnusedBits() noexcept;

    void requireValidLength(int length) const;
    void requireValidPosition(int position) const;
};


#endif // BINARY_CODE_WORD_HPP