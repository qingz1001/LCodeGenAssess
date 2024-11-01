#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// 检查在给定的最小距离下，是否可以放置所有牛
int canPlaceCows(int *positions, int n, int m, int minDist) {
    int lastPosition = positions[0];
    int count = 1; // 已经放置一头牛

    for (int i = 1; i < n; i++) {
        if (positions[i] - lastPosition >= minDist) {
            lastPosition = positions[i];
            count++;
            if (count == m) {
                return 1; // 成功放置所有牛
            }
        }
    }
    return 0; // 无法放置所有牛
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *positions = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }

    // 对牛舍位置进行排序
    qsort(positions, n, sizeof(int), compare);

    // 二分查找最大最小距离
    int left = 1; // 最小距离至少为1
    int right = positions[n - 1] - positions[0]; // 最大距离为最远的两个牛舍之间的距离
    int result = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (canPlaceCows(positions, n, m, mid)) {
            result = mid; // 更新结果
            left = mid + 1; // 尝试更大的最小距离
        } else {
            right = mid - 1; // 尝试更小的最小距离
        }
    }

    printf("%d\n", result);

    free(positions);
    return 0;
}