#include <stdio.h>

#define MAX_N 10000

int main() {
    int n, heights[MAX_N];
    int count = 0, i, left_max = 0, right_max = 0;

    // 读取输入
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    // 统计低洼地
    for (i = 1; i < n - 1; i++) {
        // 找左侧最高点
        left_max = heights[i];
        for (int j = 0; j < i; j++) {
            if (heights[j] > left_max) {
                left_max = heights[j];
            }
        }

        // 找右侧最高点
        right_max = heights[i];
        for (int j = i + 1; j < n; j++) {
            if (heights[j] > right_max) {
                right_max = heights[j];
            }
        }

        // 如果当前点比两侧最高点都低，则是一个低洼地
        if (heights[i] < left_max && heights[i] < right_max) {
            count++;
        }
    }

    // 输出结果
    printf("%d\n", count);

    return 0;
}