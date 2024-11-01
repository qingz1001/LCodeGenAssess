#include <stdio.h>

int main() {
    int apples[10]; // 存储苹果的高度
    int max_height; // 陶陶能到达的最大高度
    int count = 0;  // 可以摘到的苹果数量

    // 读取苹果的高度
    for (int i = 0; i < 10; i++) {
        scanf("%d", &apples[i]);
    }

    // 读取陶陶能到达的最大高度
    scanf("%d", &max_height);

    // 计算陶陶能够摘到的苹果数量
    for (int i = 0; i < 10; i++) {
        if (apples[i] <= max_height + 30) {
            count++;
        }
    }

    // 输出结果
    printf("%d\n", count);

    return 0;
}