#include "bit_array.h"

#include <algorithm>
#include <limits>
#include <numeric>
#include <stdexcept>

BitArray::BitArray(size_t num_bits, uint64_t value) {
    resize(num_bits);
    for (size_t i = 0;
         i < std::numeric_limits<decltype(value)>::digits && i < num_bits;
         i++) {
        bits[i] = value & 1;
        value >>= 1;
    }
}

BitArray::BitArray(const BitArray &b) : bits(b.bits) {}

void BitArray::swap(BitArray &b) { std::swap(bits, b.bits); }

BitArray &BitArray::operator=(const BitArray &b) {
    if (this != &b) {
        bits = b.bits;
    }
    return *this;
}

void BitArray::resize(size_t num_bits, bool value) {
    bits.resize(num_bits, value); // todo
}

void BitArray::clear() { bits.clear(); } // todo

void BitArray::push_back(bool bit) { bits.push_back(bit); } // todo

void BitArray::pop_back() { bits.pop_back(); }

BitArray &BitArray::operator&=(const BitArray &b) {
    for (size_t i = 0; i < bits.size() && i < b.bits.size(); i++) {
        if (!b.bits[i]) {
            reset(i);
        }
    }
    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b) {
    for (size_t i = 0; i < bits.size() && i < b.bits.size(); i++) {
        if (b.bits[i]) {
            set(i);
        }
    }
    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b) {
    for (size_t i = 0; i < bits.size() && i < b.bits.size(); i++) {
        bits[i] = bits[i] != b.bits[i];
    }
    return *this;
}

BitArray &BitArray::operator<<=(size_t n) {
    if (n >= bits.size()) {
        reset();
    } else {
        std::rotate(bits.rbegin(), bits.rbegin() + n, bits.rend());
        std::fill(bits.begin(), bits.begin() + n, false);
    }
    return *this;
}

BitArray &BitArray::operator>>=(size_t n) {
    if (n >= bits.size()) {
        reset();
    } else {
        std::rotate(bits.begin(), bits.begin() + n, bits.end());
        std::fill(bits.end() - n, bits.end(), false);
    }
    return *this;
}

BitArray BitArray::operator<<(size_t n) const {
    BitArray res = *this;
    res <<= n;
    return res;
}

BitArray BitArray::operator>>(size_t n) const {
    BitArray res = *this;
    res >>= n;
    return res;
}

BitArray &BitArray::set(size_t n, bool val) {
    if (n < 0 || n >= bits.size()) {
        throw std::invalid_argument("Error: bit index out of range");
    }
    bits[n] = true;
    return *this;
}

BitArray &BitArray::set() {
    for (size_t i = 0; i < bits.size(); i++) {
        bits[i] = true;
    }
    return *this;
}

BitArray &BitArray::reset(size_t n) {
    if (n < 0 || n >= bits.size()) {
        throw std::invalid_argument("Error: bit index out of range");
    }
    bits[n] = false;
    return *this;
}

BitArray &BitArray::reset() {
    for (size_t i = 0; i < bits.size(); i++) {
        bits[i] = false;
    }
    return *this;
}

bool BitArray::any() const {
    return std::any_of(bits.begin(), bits.end(),
                       [](bool bit) { return bit; }); // todo
}

bool BitArray::none() const {
    return std::none_of(bits.begin(), bits.end(), [](bool bit) { return bit; });
}

BitArray BitArray::operator~() const {
    BitArray res = *this;
    auto invert = [](bool bit) { return !bit; };
    std::transform(res.bits.begin(), res.bits.end(), res.bits.begin(), invert);
    return res;
}

size_t BitArray::count() const {
    return std::count(bits.begin(), bits.end(), true);
}

bool BitArray::operator[](size_t i) const { return bits[i]; }

size_t BitArray::size() const { return bits.size(); }

bool BitArray::empty() const { return bits.empty(); }

std::string BitArray::to_string() const {
    auto fold = [](std::string a, bool b) {
        return std::move(a) + std::to_string(b);
    };
    return std::accumulate(std::next(bits.rbegin()), bits.rend(),
                           std::to_string(bits.back()), fold);
}

bool operator==(const BitArray &a, const BitArray &b) {
    if (a.bits.size() != b.bits.size()) {
        return false;
    }
    return std::equal(a.bits.begin(), a.bits.end(), b.bits.begin());
}

bool operator!=(const BitArray &a, const BitArray &b) { return !(a == b); }

BitArray operator&(const BitArray &a, const BitArray &b) {
    BitArray res = a;
    res &= b;
    return res;
}

BitArray operator|(const BitArray &a, const BitArray &b) {
    BitArray res = a;
    res |= b;
    return res;
}

BitArray operator^(const BitArray &a, const BitArray &b) {
    BitArray res = a;
    res ^= b;
    return res;
}
