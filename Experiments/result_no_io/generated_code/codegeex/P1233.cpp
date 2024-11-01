#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort
int compare(const void *a, const void *b) {
    int *x = *(int **)a, *y = *(int **)b;
    if (x[0] == y[0]) return x[1] - y[1];
    return x[0] - y[0];
}

int main() {
    int n;
    scanf("%d", &n);
    int **sticks = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        sticks[i] = (int *)malloc(2 * sizeof(int));
        scanf("%d%d", &sticks[i][0], &sticks[i][1]);
    }

    // 按照长度升序，长度相同则按宽度升序排序
    qsort(sticks, n, sizeof(int *), compare);

    int ans = 1, prev_l = sticks[0][0], prev_w = sticks[0][1];
    for (int i = 1; i < n; i++) {
        if (sticks[i][0] < prev_l || sticks[i][1] < prev_w) {
            ans++;
        }
        prev_l = sticks[i][0];
        prev_w = sticks[i][1];
    }

    printf("%d\n", ans);

    for (int i = 0; i < n; i++) {
        free(sticks[i]);
    }
    free(sticks);

    return 0;
}