#include <stdio.h>

int main() {
    int num, i;
    int remainders[42] = {0};  // 用于记录余数出现情况的数组
    int distinct_count = 0;    // 不同余数的计数

    // 读取10个数字并计算它们除以42的余数
    for (i = 0; i < 10; i++) {
        scanf("%d", &num);
        remainders[num % 42] = 1;  // 标记该余数已出现
    }

    // 计算不同余数的数量
    for (i = 0; i < 42; i++) {
        if (remainders[i] == 1) {
            distinct_count++;
        }
    }

    // 输出结果
    printf("%d\n", distinct_count);

    return 0;
}