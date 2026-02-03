#include "BinaryCodeWord/BinaryCodeWord.hpp"
#include "BinaryCodeWord/detail/ErrorMessages.hpp"

#include <algorithm> // needed std::copy, std::fill_n

BinaryCodeWord::BinaryCodeWord(int length) {
    requireValidLength(length);
    m_length = length;
    m_bits = std::make_unique<int[]>(static_cast<std::size_t>(m_length));
    std::fill_n(m_bits.get(), m_length, 0);
}

BinaryCodeWord::BinaryCodeWord(const BinaryCodeWord& other)
    : m_length(other.m_length),
      m_bits(std::make_unique<int[]>(static_cast<std::size_t>(other.m_length))) {
    std::copy(other.m_bits.get(), other.m_bits.get() + other.m_length, m_bits.get());
}

BinaryCodeWord::BinaryCodeWord(BinaryCodeWord&& other) noexcept
    : m_length(other.m_length),
      m_bits(std::move(other.m_bits)) {
    other.m_length = 0;
}

BinaryCodeWord& BinaryCodeWord::operator=(const BinaryCodeWord& other) {
    if (this == &other) return *this;

    m_length = other.m_length;
    m_bits = std::make_unique<int[]>(static_cast<std::size_t>(other.m_length));
    std::copy(other.m_bits.get(), other.m_bits.get() + other.m_length, m_bits.get());
    return *this;
}

BinaryCodeWord& BinaryCodeWord::operator=(BinaryCodeWord&& other) noexcept {
    if (this == &other) return *this;

    m_length = other.m_length;
    m_bits = std::move(other.m_bits);
    other.m_length = 0;
    return *this;
}

void BinaryCodeWord::setBit(int position, int value) {
    requireValidPosition(position);
    m_bits[position] = (value & 1);
}

int BinaryCodeWord::getBit(int position) const {
    requireValidPosition(position);
    return m_bits[position];
}

BinaryCodeWord operator+(const BinaryCodeWord& a, const BinaryCodeWord& b) {
    if (a.m_length != b.m_length) {
        throw std::invalid_argument(bcw::error::length_mismatch_plus);
    }
    BinaryCodeWord out(a.m_length);
    // Component-wise XOR using integer ^. Supports chaining: ((a+b)+c) etc.
    for (int i = 0; i < a.m_length; ++i) {
        out.m_bits[i] = (a.m_bits[i] ^ b.m_bits[i]) & 1;
    }
    return out;
}

BinaryCodeWord& BinaryCodeWord::operator+=(const BinaryCodeWord& rhs) {
    if (m_length != rhs.m_length) {
        throw std::invalid_argument(bcw::error::length_mismatch_pluseq);
    }
    // In-place XOR is ideal for multiple XOR operations.
    for (int i = 0; i < m_length; ++i) {
        m_bits[i] = (m_bits[i] ^ rhs.m_bits[i]) & 1;
    }
    return *this;
}

bool BinaryCodeWord::operator==(const BinaryCodeWord& rhs) const noexcept {
    if (m_length != rhs.m_length) return false;
    for (int i = 0; i < m_length; ++i) {
        if ((m_bits[i] & 1) != (rhs.m_bits[i] & 1)) return false;
    }
    return true;
}

void BinaryCodeWord::requireValidLength(int length) const {
    if (length <= 0) {
        throw std::invalid_argument(bcw::error::length_nonpositive);
    }
}

void BinaryCodeWord::requireValidPosition(int position) const {
    if (position < 0 || position >= m_length) {
        throw std::out_of_range(bcw::error::position_oob);
    }
}
