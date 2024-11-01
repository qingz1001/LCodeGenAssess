#include <stdio.h>

int main() {
    unsigned int num;
    scanf("%u", &num);

    unsigned int high = num >> 16; // 获取高16位
    unsigned int low = num & 0xFFFF; // 获取低16位

    unsigned int new_num = (low << 16) | high; // 交换高低位

    printf("%u\n", new_num);

    return 0;
}