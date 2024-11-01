#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d", &n);
    int cakes[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &cakes[i]);
    }
    scanf("%d", &m);
    int mouths[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &mouths[i]);
    }

    // 对蛋糕和嘴巴的大小进行排序
    qsort(cakes, n, sizeof(int), (int (*)(const void *, const void *))strcmp);
    qsort(mouths, m, sizeof(int), (int (*)(const void *, const void *))strcmp);

    int i = 0, j = 0, count = 0;
    while (i < n && j < m) {
        if (cakes[i] >= mouths[j]) {
            count++;
            i++;
            j++;
        } else {
            i++;
        }
    }

    printf("%d\n", count);
    return 0;
}