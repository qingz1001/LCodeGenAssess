#include <stdio.h>

int main() {
    int a[10], i, j, count = 0;
    int visited[42] = {0}; // 用于记录余数是否已经出现过

    // 输入10个整数
    for (i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
        a[i] %= 42; // 计算模42的结果
    }

    // 统计不同的余数
    for (i = 0; i < 10; i++) {
        if (visited[a[i]] == 0) { // 如果这个余数还没有出现过
            visited[a[i]] = 1; // 标记为已经出现
            count++; // 计数不同的余数
        }
    }

    // 输出不同的余数的数量
    printf("%d\n", count);

    return 0;
}