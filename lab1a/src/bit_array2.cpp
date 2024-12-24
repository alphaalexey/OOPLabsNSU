#include "bit_array2.h"

#include <algorithm>
#include <bitset>
#include <cstring>
#include <stdexcept>

BitArray::BitArray() : bits_size(0), bits(nullptr) {}

BitArray::~BitArray() { delete[] bits; }

BitArray::BitArray(size_t num_bits, uint64_t value) : bits_size(num_bits) {
    size_t bytes = (num_bits + 7) / 8;
    bits = new unsigned char[bytes];
    std::memset(bits, 0, bytes); // Initialize all bits to 0

    std::memcpy(bits, &value, std::min(sizeof(value), bytes));
}

BitArray::BitArray(const BitArray &b) : bits_size(b.bits_size) {
    size_t bytes = (bits_size + 7) / 8;
    bits = new unsigned char[bytes];
    std::memcpy(bits, b.bits, bytes);
}

void BitArray::swap(BitArray &b) {
    std::swap(bits_size, b.bits_size);
    std::swap(bits, b.bits);
}

BitArray &BitArray::operator=(const BitArray &b) {
    if (this != &b) {
        BitArray temp(b);
        swap(temp);
    }
    return *this;
}

void BitArray::resize(size_t num_bits, bool value) {
    size_t new_bytes = (num_bits + 7) / 8;
    size_t old_bytes = (bits_size + 7) / 8;
    
    bits_size = num_bits;

    if (new_bytes == old_bytes)
        return;

    unsigned char *new_bits = new unsigned char[new_bytes];
    std::memset(new_bits, value * 0xFF, new_bytes);

    if (bits) {
        std::memcpy(new_bits, bits, std::min(old_bytes, new_bytes));
        delete[] bits;
    }
    bits = new_bits;
}

void BitArray::clear() {
    delete[] bits;
    bits = nullptr;
    bits_size = 0;
}

void BitArray::push_back(bool bit) {
    resize(bits_size + 1, false);
    set(bits_size - 1, bit);
}

void BitArray::pop_back() {
    if (bits_size > 0) {
        resize(bits_size - 1, false);
    }
}

BitArray &BitArray::operator&=(const BitArray &b) {
    size_t min_bits = std::min(bits_size, b.bits_size);
    for (size_t i = 0; i < (min_bits + 7) / 8; ++i) {
        bits[i] &= b.bits[i];
    }
    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b) {
    size_t min_bits = std::min(bits_size, b.bits_size);
    for (size_t i = 0; i < (min_bits + 7) / 8; ++i) {
        bits[i] |= b.bits[i];
    }
    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b) {
    size_t min_bits = std::min(bits_size, b.bits_size);
    for (size_t i = 0; i < (min_bits + 7) / 8; ++i) {
        bits[i] ^= b.bits[i];
    }
    return *this;
}

BitArray &BitArray::set(size_t n, bool val) {
    if (n >= bits_size) {
        throw std::out_of_range("Index out of range");
    }
    size_t byte_index = n / 8;
    size_t bit_index = n % 8;
    if (val) {
        bits[byte_index] |= (1 << bit_index);
    } else {
        bits[byte_index] &= ~(1 << bit_index);
    }
    return *this;
}

BitArray &BitArray::set() {
    std::memset(bits, 0xFF, (bits_size + 7) / 8);
    return *this;
}

BitArray &BitArray::reset(size_t n) { return set(n, false); }

BitArray &BitArray::reset() {
    std::memset(bits, 0, (bits_size + 7) / 8);
    return *this;
}

bool BitArray::any() const {
    for (size_t i = 0; i < (bits_size + 7) / 8; ++i) {
        if (bits[i] != 0)
            return true;
    }
    return false;
}

bool BitArray::none() const { return !any(); }

BitArray BitArray::operator~() const {
    BitArray temp(*this);
    for (size_t i = 0; i < (bits_size + 7) / 8; ++i) {
        temp.bits[i] = ~bits[i];
    }
    return temp;
}

size_t BitArray::count() const {
    size_t cnt = 0;
    for (size_t i = 0; i < bits_size; ++i) {
        if ((*this)[i])
            ++cnt;
    }
    return cnt;
}

bool BitArray::operator[](size_t i) const {
    if (i >= bits_size)
        throw std::out_of_range("Index out of range");
    size_t byte_index = i / 8;
    size_t bit_index = i % 8;
    return bits[byte_index] & (1 << bit_index);
}

size_t BitArray::size() const { return bits_size; }

bool BitArray::empty() const { return bits_size == 0; }

std::string BitArray::to_string() const {
    std::string result;
    for (size_t i = bits_size; i > 0; i--) {
        result.push_back((*this)[i - 1] + '0');
    }
    return result;
}

bool operator==(const BitArray &a, const BitArray &b) {
    if (a.bits_size != b.bits_size)
        return false;
    return std::memcmp(a.bits, b.bits, (a.bits_size + 7) / 8) == 0;
}

bool operator!=(const BitArray &a, const BitArray &b) { return !(a == b); }

BitArray operator&(const BitArray &b1, const BitArray &b2) {
    BitArray temp(b1);
    return temp &= b2;
}

BitArray operator|(const BitArray &b1, const BitArray &b2) {
    BitArray temp(b1);
    return temp |= b2;
}

BitArray operator^(const BitArray &b1, const BitArray &b2) {
    BitArray temp(b1);
    return temp ^= b2;
}
