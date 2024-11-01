#include <stdio.h>
#include <stdint.h>

uint32_t swapBits(uint32_t num) {
    uint32_t high = (num >> 16) & 0xFFFF;
    uint32_t low = num & 0xFFFF;
    return (low << 16) | high;
}

int main() {
    uint32_t num;
    scanf("%u", &num);
    uint32_t result = swapBits(num);
    printf("%u\n", result);
    return 0;
}