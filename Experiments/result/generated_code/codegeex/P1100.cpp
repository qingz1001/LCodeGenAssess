#include <stdio.h>

int main() {
    unsigned int num;
    scanf("%u", &num);
    
    unsigned int high = num >> 16;
    unsigned int low = num << 16;
    
    unsigned int result = high | low;
    
    printf("%u\n", result);
    
    return 0;
}