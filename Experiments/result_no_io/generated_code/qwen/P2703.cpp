#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

int main() {
    int n;
    scanf("%d", &n);
    int *L = (int *)malloc(n * sizeof(int));
    int *R = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &L[i], &R[i]);
    }

    // 计算初始状态下的格子数
    long long initial_cells = 0;
    for (int i = 0; i < n; i++) {
        initial_cells += R[i] - L[i] + 1;
    }

    // 计算目标状态下的格子数
    long long target_cells = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            target_cells += R[i] - L[i];
        } else if (i == n - 1) {
            target_cells += R[i] - L[i];
        } else {
            target_cells += R[i] - L[i] - 1;
        }
    }

    // 最小代价即为两者的差值
    long long min_cost = initial_cells - target_cells;

    printf("%lld\n", min_cost);

    free(L);
    free(R);
    return 0;
}