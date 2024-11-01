#include <stdio.h>
#include <stdlib.h>

// 计算两点之间的距离平方
int distanceSquared(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
    int x1, y1, x2, y2, N;
    scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &N);

    int *missilesX = (int *)malloc(N * sizeof(int));
    int *missilesY = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &missilesX[i], &missilesY[i]);
    }

    // 计算每个导弹到两个拦截系统的距离平方
    int *distancesToSystem1 = (int *)malloc(N * sizeof(int));
    int *distancesToSystem2 = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        distancesToSystem1[i] = distanceSquared(x1, y1, missilesX[i], missilesY[i]);
        distancesToSystem2[i] = distanceSquared(x2, y2, missilesX[i], missilesY[i]);
    }

    // 对每个导弹的距离进行排序
    int *sortedDistancesToSystem1 = (int *)malloc(N * sizeof(int));
    int *sortedDistancesToSystem2 = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        sortedDistancesToSystem1[i] = distancesToSystem1[i];
        sortedDistancesToSystem2[i] = distancesToSystem2[i];
    }
    qsort(sortedDistancesToSystem1, N, sizeof(int), (int (*)(const void *, const void *))strcmp);
    qsort(sortedDistancesToSystem2, N, sizeof(int), (int (*)(const void *, const void *))strcmp);

    // 尝试不同的拦截顺序，找到最小代价
    int minCost = INT_MAX;
    for (int i = 0; i <= N; i++) {
        int cost1 = 0, cost2 = 0;
        for (int j = 0; j < i; j++) {
            cost1 += sortedDistancesToSystem1[j];
        }
        for (int j = i; j < N; j++) {
            cost2 += sortedDistancesToSystem2[j];
        }
        int currentCost = cost1 + cost2;
        if (currentCost < minCost) {
            minCost = currentCost;
        }
    }

    printf("%d\n", minCost);

    free(missilesX);
    free(missilesY);
    free(distancesToSystem1);
    free(distancesToSystem2);
    free(sortedDistancesToSystem1);
    free(sortedDistancesToSystem2);

    return 0;
}