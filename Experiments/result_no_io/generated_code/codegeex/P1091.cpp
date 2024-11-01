#include <stdio.h>
#include <stdlib.h>

#define MAXN 101

int main() {
    int n;
    scanf("%d", &n);
    int heights[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    // 计算从左到右的最长递增子序列长度
    int left[MAXN];
    for (int i = 0; i < n; i++) {
        left[i] = 1;
        for (int j = 0; j < i; j++) {
            if (heights[i] > heights[j] && left[i] < left[j] + 1) {
                left[i] = left[j] + 1;
            }
        }
    }

    // 计算从右到左的最长递增子序列长度
    int right[MAXN];
    for (int i = n - 1; i >= 0; i--) {
        right[i] = 1;
        for (int j = n - 1; j > i; j--) {
            if (heights[i] > heights[j] && right[i] < right[j] + 1) {
                right[i] = right[j] + 1;
            }
        }
    }

    // 计算合唱队形的最大长度
    int max_length = 0;
    for (int i = 0; i < n; i++) {
        if (left[i] + right[i] - 1 > max_length) {
            max_length = left[i] + right[i] - 1;
        }
    }

    // 输出最少需要出列的同学数
    printf("%d\n", n - max_length);

    return 0;
}