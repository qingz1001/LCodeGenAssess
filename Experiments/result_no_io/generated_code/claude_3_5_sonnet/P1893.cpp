#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);

    int heights[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }

    int max_width = 0;
    int left[MAX_N], right[MAX_N];

    // 计算每个点左边的连续上升（或相等）序列长度
    left[0] = 1;
    for (int i = 1; i < N; i++) {
        if (heights[i] >= heights[i-1]) {
            left[i] = left[i-1] + 1;
        } else {
            left[i] = 1;
        }
    }

    // 计算每个点右边的连续下降（或相等）序列长度
    right[N-1] = 1;
    for (int i = N-2; i >= 0; i--) {
        if (heights[i] >= heights[i+1]) {
            right[i] = right[i+1] + 1;
        } else {
            right[i] = 1;
        }
    }

    // 计算最大宽度
    for (int i = 0; i < N; i++) {
        max_width = max(max_width, left[i] + right[i] - 1);
    }

    printf("%d\n", max_width);

    return 0;
}