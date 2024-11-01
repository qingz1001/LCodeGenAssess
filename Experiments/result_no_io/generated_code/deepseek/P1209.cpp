#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int m, s, c;
    scanf("%d %d %d", &m, &s, &c);

    int stalls[c];
    for (int i = 0; i < c; i++) {
        scanf("%d", &stalls[i]);
    }

    // 对牛棚编号进行排序
    qsort(stalls, c, sizeof(int), compare);

    // 计算相邻牛棚之间的间隔
    int gaps[c - 1];
    for (int i = 0; i < c - 1; i++) {
        gaps[i] = stalls[i + 1] - stalls[i] - 1;
    }

    // 对间隔进行排序
    qsort(gaps, c - 1, sizeof(int), compare);

    // 计算最小总长度
    int total_length = stalls[c - 1] - stalls[0] + 1;
    for (int i = 0; i < m - 1 && i < c - 1; i++) {
        total_length -= gaps[c - 2 - i];
    }

    printf("%d\n", total_length);

    return 0;
}