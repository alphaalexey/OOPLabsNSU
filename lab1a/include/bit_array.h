#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

class BitArray {
public:
    BitArray() = default;
    ~BitArray() = default;

    /*!
     * Construct a BitArray of `num_bits` bits with `value` in the first 64
     * bits. The remaining bits are initialized to 0.
     *
     * @param num_bits The number of bits in the new BitArray.
     * @param value The value to initialize the first 64 bits with. Defaults to
     * 0.
     */
    explicit BitArray(size_t num_bits, uint64_t value = 0);

    /*!
     * Copy the contents of `b` into this BitArray.
     * @param b The BitArray to copy from.
     */
    BitArray(const BitArray &b);

    /*!
     * Swap the contents of this BitArray with `b`.
     * @param b The BitArray to swap with.
     */
    void swap(BitArray &b);

    /*!
     * Copy the contents of `b` into this BitArray.
     * @param b The BitArray to copy from.
     */
    BitArray &operator=(const BitArray &b);

    /*!
     * Resize the BitArray to `num_bits` bits and initialize the new bits to
     * `value`. If `num_bits` is less than the current number of bits, any
     * excess bits are removed.
     * @param num_bits The number of bits the BitArray should have after
     * resizing.
     * @param value The value to initialize the new bits with. Defaults to
     * false.
     */
    void resize(size_t num_bits, bool value = false);

    /*!
     * Clear the BitArray, removing all bits.
     */
    void clear();

    /*!
     * Add a bit to the end of the BitArray with the value `bit`.
     * @param bit The value of the bit to add.
     */
    void push_back(bool bit);

    /*!
     * Remove last bit of the BitArray
     */
    void pop_back();

    /*!
     * Set the bits in `b` as the bits in the current BitArray.
     * @param b The BitArray to copy from.
     */
    BitArray &operator&=(const BitArray &b);

    /*!
     * OR the bits in `b` with the current BitArray.
     * @param b The BitArray to OR with.
     */
    BitArray &operator|=(const BitArray &b);

    /*!
     * XOR the bits in `b` with the current BitArray.
     * @param b The BitArray to XOR with.
     */
    BitArray &operator^=(const BitArray &b);

    /*!
     * Shift the bits in the current BitArray to the left by `n`.
     * @param n The number of bits to shift by.
     */
    BitArray &operator<<=(size_t n);

    /*!
     * Shift the bits in the current BitArray to the right by `n`.
     * @param n The number of bits to shift by.
     */
    BitArray &operator>>=(size_t n);

    /*!
     * Create a new BitArray with the bits shifted to the left by `n`.
     * @param n The number of bits to shift by.
     */
    BitArray operator<<(size_t n) const;

    /*!
     * Create a new BitArray with the bits shifted to the right by `n`.
     * @param n The number of bits to shift by.
     */
    BitArray operator>>(size_t n) const;

    /*!
     * Set the bit at `n` to `val`.
     * @param n The index of the bit to set.
     * @param val The value to set the bit to. Defaults to true.
     */
    BitArray &set(size_t n, bool val = true);

    /*!
     * Set all the bits in the current BitArray to `val`.
     * @param val The value to set all the bits to. Defaults to true.
     */
    BitArray &set();

    /*!
     * Reset the bit at `n` to `val`.
     * @param n The index of the bit to reset.
     * @param val The value to reset the bit to. Defaults to false.
     */
    BitArray &reset(size_t n);

    /*!
     * Reset all the bits in the current BitArray to `val`.
     * @param val The value to reset all the bits to. Defaults to false.
     */
    BitArray &reset();

    /*!
     * Returns true if any of the bits are set.
     */
    bool any() const;

    /*!
     * Returns true if none of the bits are set.
     */
    bool none() const;

    /*!
     * Create a new BitArray with the bits inverted.
     */
    BitArray operator~() const;

    /*!
     * Returns the number of bits that are set.
     */
    size_t count() const;

    /*!
     * Returns the value of the bit at `i`.
     * @param n The index of the bit to get.
     */
    bool operator[](size_t i) const;

    /*!
     * Returns the number of bits in the current BitArray.
     */
    size_t size() const;

    /*!
     * Returns true if the current BitArray is empty.
     */
    bool empty() const;

    /*!
     * Returns a string representation of the current BitArray.
     */
    std::string to_string() const;

    /*!
     * Compare two BitArrays for equality.
     * @param a The first BitArray to compare.
     * @param b The second BitArray to compare.
     * @return true if `a` and `b` are equal, false otherwise.
     */
    friend bool operator==(const BitArray &a, const BitArray &b);

    /*!
     * Compare two BitArrays for inequality.
     * @param a The first BitArray to compare.
     * @param b The second BitArray to compare.
     * @return true if `a` and `b` are not equal, false otherwise.
     */
    friend bool operator!=(const BitArray &a, const BitArray &b);

    /*!
     * AND the bits in `b1` and `b2`.
     * @param b1 The first BitArray to AND.
     * @param b2 The second BitArray to AND.
     */
    friend BitArray operator&(const BitArray &b1, const BitArray &b2);

    /*!
     * OR the bits in `b1` and `b2`.
     * @param b1 The first BitArray to OR.
     * @param b2 The second BitArray to OR.
     */
    friend BitArray operator|(const BitArray &b1, const BitArray &b2);

    /*!
     * XOR the bits in `b1` and `b2`.
     * @param b1 The first BitArray to XOR.
     * @param b2 The second BitArray to XOR.
     */
    friend BitArray operator^(const BitArray &b1, const BitArray &b2);

private:
    std::vector<bool> bits{};
};
