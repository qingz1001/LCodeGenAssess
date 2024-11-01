#include <stdio.h>

int main() {
    unsigned int num;
    scanf("%u", &num);
    unsigned int high = (num >> 16) & 0xFFFF;
    unsigned int low = num & 0xFFFF;
    unsigned int swapped = (low << 16) | high;
    printf("%u\n", swapped);
    return 0;
}