#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int heights[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }

    int max_width = 0;
    int start = 0;
    while (start < N) {
        int end = start;
        // 找到上升部分
        while (end + 1 < N && heights[end + 1] >= heights[end]) {
            end++;
        }
        // 找到下降部分
        while (end + 1 < N && heights[end + 1] <= heights[end]) {
            end++;
        }
        // 计算山的宽度
        int width = end - start + 1;
        if (width > max_width) {
            max_width = width;
        }
        // 移动到下一个可能的山峰开始位置
        start = end;
        while (start + 1 < N && heights[start + 1] <= heights[start]) {
            start++;
        }
        start++;
    }

    printf("%d\n", max_width);
    return 0;
}