#include <stdio.h>

int main() {
    int apple_heights[10];
    int max_reach, count = 0;

    // 读取苹果的高度
    for (int i = 0; i < 10; i++) {
        scanf("%d", &apple_heights[i]);
    }

    // 读取陶陶的最大高度
    scanf("%d", &max_reach);

    // 计算陶陶能够摘到的苹果数目
    for (int i = 0; i < 10; i++) {
        if (apple_heights[i] <= max_reach + 30) {
            count++;
        }
    }

    // 输出结果
    printf("%d\n", count);

    return 0;
}