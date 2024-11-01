#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *water = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &water[i]);
    }

    // 排序接水量数组
    qsort(water, n, sizeof(int), compare);

    int *tanks = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        tanks[i] = water[i];
    }

    int seconds = 0;
    int index = m;
    while (index < n) {
        int minTank = tanks[0];
        int minTankIndex = 0;
        for (int i = 1; i < m; i++) {
            if (tanks[i] < minTank) {
                minTank = tanks[i];
                minTankIndex = i;
            }
        }

        tanks[minTankIndex] += water[index];
        index++;
        seconds++;
    }

    // 找到最大值即为所需的总时间
    int maxTank = tanks[0];
    for (int i = 1; i < m; i++) {
        if (tanks[i] > maxTank) {
            maxTank = tanks[i];
        }
    }

    printf("%d\n", maxTank);

    free(water);
    free(tanks);
    return 0;
}