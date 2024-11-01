#include <stdio.h>

int main(){
    unsigned int x;
    scanf("%u", &x);
    unsigned int high = (x >> 16) & 0xFFFF;
    unsigned int low = x & 0xFFFF;
    unsigned int swapped = (low << 16) | high;
    printf("%u\n", swapped);
    return 0;
}