#include <stdio.h>
#include <stdlib.h>

// 函数声明
int cmp(const void *a, const void *b);

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    // 分配数组空间
    int *marbles = (int *)malloc(M * sizeof(int));

    // 读取每个颜色弹珠的数量
    for (int i = 0; i < M; i++) {
        scanf("%d", &marbles[i]);
    }

    // 对弹珠数量进行排序
    qsort(marbles, M, sizeof(int), cmp);

    // 初始化二分查找的左右边界
    int left = 1, right = marbles[0], mid;
    int minJealousy = right;

    // 二分查找最小嫉妒值
    while (left <= right) {
        mid = (left + right) / 2;
        int children = 0;
        int remainingMarbles = 0;

        // 计算需要的最小孩子数
        for (int i = 0; i < M; i++) {
            children += (marbles[i] + mid - 1) / mid;
            if (children > N) {
                break;
            }
            remainingMarbles += marbles[i] % mid;
        }

        // 如果孩子数不超过N，尝试减小嫉妒值
        if (children <= N) {
            minJealousy = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    // 输出最小的嫉妒值
    printf("%d\n", minJealousy);

    // 释放内存
    free(marbles);

    return 0;
}

// 比较函数，用于qsort
int cmp(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}