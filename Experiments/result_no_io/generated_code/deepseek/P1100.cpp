#include <stdio.h>

unsigned int swap_high_low(unsigned int num) {
    unsigned int high = num >> 16;
    unsigned int low = num & 0xFFFF;
    return (low << 16) | high;
}

int main() {
    unsigned int num;
    scanf("%u", &num);
    printf("%u\n", swap_high_low(num));
    return 0;
}