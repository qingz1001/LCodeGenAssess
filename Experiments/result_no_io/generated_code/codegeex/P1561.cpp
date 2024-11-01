#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);

    int u[25001], d[25001];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &u[i], &d[i]);
    }

    // 按照上山的用时从大到小排序
    qsort(u, n, sizeof(int), compare);
    qsort(d, n, sizeof(int), compare);

    int max_up = u[0];
    int sum_down = 0;

    for (int i = 0; i < n; i++) {
        sum_down += d[i];
        if (sum_down > max_up) {
            max_up = sum_down;
        }
    }

    // 输出最短时间
    printf("%d\n", max_up);
    return 0;
}