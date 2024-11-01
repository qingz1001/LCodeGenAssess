#include <stdio.h>

int main() {
    int n, b;
    scanf("%d %d", &n, &b);
    int heights[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    // 对奶牛身高进行降序排序
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (heights[j] < heights[j + 1]) {
                int temp = heights[j];
                heights[j] = heights[j + 1];
                heights[j + 1] = temp;
            }
        }
    }

    int sum = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        sum += heights[i];
        count++;
        if (sum >= b) {
            break;
        }
    }

    printf("%d\n", count);
    return 0;
}