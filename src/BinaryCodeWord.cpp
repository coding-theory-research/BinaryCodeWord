#include "BinaryCodeWord/BinaryCodeWord.hpp"
#include "BinaryCodeWord/detail/ErrorMessages.hpp"
#include <algorithm>
#include <ostream>

BinaryCodeWord::BinaryCodeWord(int length) {
    requireValidLength(length);
    m_length = length;
    m_numWords = computeNumWords(m_length);

    m_words = std::make_unique<word_t[]>(static_cast<std::size_t>(m_numWords));
    std::fill_n(m_words.get(), m_numWords, word_t{0});
}

BinaryCodeWord::BinaryCodeWord(const BinaryCodeWord& other)
    : m_length(other.m_length),
      m_numWords(other.m_numWords),
      m_words(std::make_unique<word_t[]>(static_cast<std::size_t>(other.m_numWords))) {
    std::copy(other.m_words.get(),
              other.m_words.get() + other.m_numWords,
              m_words.get());
}

BinaryCodeWord::BinaryCodeWord(BinaryCodeWord&& other) noexcept
    : m_length(other.m_length),
      m_numWords(other.m_numWords),
      m_words(std::move(other.m_words)) {
    other.m_length = 0;
    other.m_numWords = 0;
}

BinaryCodeWord& BinaryCodeWord::operator=(const BinaryCodeWord& other) {
    if (this == &other) return *this;
    m_length = other.m_length;
    m_numWords = other.m_numWords;
    m_words = std::make_unique<word_t[]>(static_cast<std::size_t>(m_numWords));
    std::copy(other.m_words.get(),
              other.m_words.get() + other.m_numWords,
              m_words.get());
    return *this;
}

BinaryCodeWord& BinaryCodeWord::operator=(BinaryCodeWord&& other) noexcept {
    if (this == &other) return *this;
    m_length = other.m_length;
    m_numWords = other.m_numWords;
    m_words = std::move(other.m_words);
    other.m_length = 0;
    other.m_numWords = 0;
    return *this;
}

void BinaryCodeWord::setBit(int position, int value) {
    requireValidPosition(position);
    const int w = position / WORD_BITS;
    const int b = position % WORD_BITS;
    const word_t mask = (word_t{1} << b);

    if (value & 1)
        m_words[w] |= mask;
    else
        m_words[w] &= ~mask;
}

int BinaryCodeWord::getBit(int position) const {
    requireValidPosition(position);
    const int w = position / WORD_BITS;
    const int b = position % WORD_BITS;
    const word_t mask = (word_t{1} << b);
    return (m_words[w] & mask) ? 1 : 0;
}

bool BinaryCodeWord::isZero() const noexcept {
    for (int i = 0; i < m_numWords; ++i)
        if (m_words[i] != 0) return false;
    return true;
}

BinaryCodeWord operator+(const BinaryCodeWord& a,
                          const BinaryCodeWord& b) {
    if (a.m_length != b.m_length)
        throw std::invalid_argument(bcw::error::length_mismatch_plus);

    BinaryCodeWord out(a.m_length);
    for (int i = 0; i < a.m_numWords; ++i)
        out.m_words[i] = a.m_words[i] ^ b.m_words[i];

    out.maskUnusedBits();
    return out;
}

BinaryCodeWord& BinaryCodeWord::operator+=(const BinaryCodeWord& rhs) {
    if (m_length != rhs.m_length)
        throw std::invalid_argument(bcw::error::length_mismatch_pluseq);

    for (int i = 0; i < m_numWords; ++i)
        m_words[i] ^= rhs.m_words[i];

    maskUnusedBits();
    return *this;
}

bool BinaryCodeWord::operator==(const BinaryCodeWord& rhs) const noexcept {
    if (m_length != rhs.m_length) return false;
    for (int i = 0; i < m_numWords; ++i)
        if (m_words[i] != rhs.m_words[i]) return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const BinaryCodeWord& w) {
    os << '(';
    for (int i = 0; i < w.length(); ++i) {
        os << w.getBit(i);
    }
    os << ')';
    return os;
}

void BinaryCodeWord::maskUnusedBits() noexcept {
    const int used = m_length % WORD_BITS;
    if (used == 0 || m_numWords == 0) return;

    const word_t mask =
        (used == WORD_BITS) ? ~word_t{0} : ((word_t{1} << used) - 1);

    m_words[m_numWords - 1] &= mask;
}

void BinaryCodeWord::requireValidLength(int length) const {
    if (length <= 0)
        throw std::invalid_argument(bcw::error::length_nonpositive);
}

void BinaryCodeWord::requireValidPosition(int position) const {
    if (position < 0 || position >= m_length)
        throw std::out_of_range(bcw::error::position_oob);
}
