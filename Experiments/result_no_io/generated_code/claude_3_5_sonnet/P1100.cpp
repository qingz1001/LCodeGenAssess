#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t num;
    scanf("%u", &num);
    
    uint32_t high = num >> 16;  // 获取高16位
    uint32_t low = num & 0xFFFF;  // 获取低16位
    
    uint32_t result = (low << 16) | high;  // 交换高低位
    
    printf("%u\n", result);
    
    return 0;
}