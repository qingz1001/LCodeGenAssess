#include <stdio.h>

int main() {
    unsigned int num;
    scanf("%u", &num);
    
    unsigned int high = num >> 16;
    unsigned int low = num & 0xFFFF;
    unsigned int result = (low << 16) | high;
    
    printf("%u\n", result);
    
    return 0;
}