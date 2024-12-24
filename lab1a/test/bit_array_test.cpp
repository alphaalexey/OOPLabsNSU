#include "bit_array.h"
#include <gtest/gtest.h>

// Тест конструктора и начальной инициализации
TEST(BitArrayTest, ConstructorDefault) {
    BitArray bits;
    EXPECT_TRUE(bits.empty());
    EXPECT_EQ(bits.size(), 0);
}

// Тест конструктора с инициализацией value
TEST(BitArrayTest, ConstructorWithValue) {
    BitArray bits(10, 0b1011);
    EXPECT_EQ(bits.size(), 10);
    EXPECT_EQ(bits[0], true);
    EXPECT_EQ(bits[1], true);
    EXPECT_EQ(bits[2], false);
    EXPECT_EQ(bits[3], true);
}

// Тест копирующего конструктора
TEST(BitArrayTest, CopyConstructor) {
    BitArray original(5, 0b10101);
    BitArray copy(original);
    EXPECT_EQ(copy.size(), 5);
    EXPECT_EQ(copy.to_string(), "10101");
}

// Тест оператора присваивания
TEST(BitArrayTest, AssignmentOperator) {
    BitArray bits1(5, 0b110);
    BitArray bits2 = bits1;
    EXPECT_EQ(bits2.to_string(), bits1.to_string());
}

// Тест функции resize
TEST(BitArrayTest, Resize) {
    BitArray bits(5, 0b10101);
    bits.resize(8);
    EXPECT_EQ(bits.size(), 8);
    EXPECT_EQ(bits[5], false);
    EXPECT_EQ(bits[6], false);
    EXPECT_EQ(bits[7], false);

    bits.resize(3);
    EXPECT_EQ(bits.size(), 3);
    EXPECT_EQ(bits.to_string(), "101");
}

// Тест побитовой операции AND
TEST(BitArrayTest, BitwiseAND) {
    BitArray bits1(4, 0b1010);
    BitArray bits2(4, 0b1100);
    BitArray result = bits1 & bits2;
    EXPECT_EQ(result.to_string(), "1000");
}

// Тест побитовой операции OR
TEST(BitArrayTest, BitwiseOR) {
    BitArray bits1(4, 0b1010);
    BitArray bits2(4, 0b1100);
    BitArray result = bits1 | bits2;
    EXPECT_EQ(result.to_string(), "1110");
}

// Тест побитовой операции XOR
TEST(BitArrayTest, BitwiseXOR) {
    BitArray bits1(4, 0b1010);
    BitArray bits2(4, 0b1100);
    BitArray result = bits1 ^ bits2;
    EXPECT_EQ(result.to_string(), "0110");
}

// Тест оператора сдвига влево
TEST(BitArrayTest, LeftShiftOperator) {
    BitArray bits(4, 0b1010);
    BitArray result = bits << 2;
    EXPECT_EQ(result.to_string(), "1000");
}

// Тест оператора сдвига вправо
TEST(BitArrayTest, RightShiftOperator) {
    BitArray bits(4, 0b1010);
    BitArray result = bits >> 2;
    EXPECT_EQ(result.to_string(), "0010");
}

// Тест функции set
TEST(BitArrayTest, SetBits) {
    BitArray bits(5);
    bits.set(0);
    bits.set(3);
    EXPECT_EQ(bits.to_string(), "01001");
}

// Тест функции reset
TEST(BitArrayTest, ResetBits) {
    BitArray bits(5, 0b11111);
    bits.reset(0);
    bits.reset(3);
    EXPECT_EQ(bits.to_string(), "10110");
}

// Тест функции reset для всех битов
TEST(BitArrayTest, ResetAllBits) {
    BitArray bits(5, 0b11111);
    bits.reset();
    EXPECT_TRUE(bits.none());
}

// Тест функции any
TEST(BitArrayTest, AnyBitsSet) {
    BitArray bits(5, 0b10100);
    EXPECT_TRUE(bits.any());
    bits.reset();
    EXPECT_FALSE(bits.any());
}

// Тест функции none
TEST(BitArrayTest, NoBitsSet) {
    BitArray bits(5);
    EXPECT_TRUE(bits.none());
    bits.set(0);
    EXPECT_FALSE(bits.none());
}

// Тест функции count
TEST(BitArrayTest, CountBitsSet) {
    BitArray bits(5, 0b10101);
    EXPECT_EQ(bits.count(), 3);
}

// Тест функции to_string
TEST(BitArrayTest, ToString) {
    BitArray bits(5, 0b10101);
    EXPECT_EQ(bits.to_string(), "10101");
}

// Тест оператора ==
TEST(BitArrayTest, EqualityOperator) {
    BitArray bits1(5, 0b10101);
    BitArray bits2(5, 0b10101);
    EXPECT_TRUE(bits1 == bits2);
}

// Тест оператора !=
TEST(BitArrayTest, InequalityOperator) {
    BitArray bits1(5, 0b10101);
    BitArray bits2(5, 0b11011);
    EXPECT_TRUE(bits1 != bits2);
}
