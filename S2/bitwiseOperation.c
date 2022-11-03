#include <stdint.h>
#include <stdio.h>
// Write the body of a function get_3_leftmost_bits that returns the 3 high order bits of x.

// For instance, if x=0b11011001..., the function should return a uint8_t containing 0b00000110.

// If x=0b01100001..., the function should return a uint8_t containing 0b00000011.

uint8_t get_3_leftmost_bits(uint32_t x) {
    return (x >> 29) & 0x7;
}

uint8_t get_4_rightmost_bits(uint32_t x) {
        return x & 0xF;
}

uint32_t cycle_bits(uint32_t x, uint8_t n) {
    return (x << n) | (x >> (32 - n));
}

uint8_t nbits(uint32_t n) {
    uint8_t count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

uint32_t reset_highestorder_strong_bit(uint32_t x) {
    for (int i=31; i >= 0; --i) {
        if (x & (1 << i)) return x & (~(1<<i));
    }
    return x;
}

int main() {
    printf("%d", reset_highestorder_strong_bit(0b01111111111111111111111111111111));
    return 0;
}

