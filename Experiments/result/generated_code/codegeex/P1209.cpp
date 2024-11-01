#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int m, s, c;
    scanf("%d %d %d", &m, &s, &c);

    int *cow_positions = (int*)malloc(c * sizeof(int));
    for (int i = 0; i < c; i++) {
        scanf("%d", &cow_positions[i]);
    }

    // 对牛所在的牛棚位置进行排序
    qsort(cow_positions, c, sizeof(int), compare);

    // 计算相邻牛棚之间的间隔
    int *gaps = (int*)malloc((c - 1) * sizeof(int));
    for (int i = 0; i < c - 1; i++) {
        gaps[i] = cow_positions[i + 1] - cow_positions[i] - 1;
    }

    // 对间隔进行排序
    qsort(gaps, c - 1, sizeof(int), compare);

    // 计算最少木板总长度
    int total_length = cow_positions[c - 1] - cow_positions[0] + 1;
    for (int i = 0; i < c - m + 1; i++) {
        total_length -= gaps[i];
    }

    printf("%d\n", total_length);

    free(cow_positions);
    free(gaps);

    return 0;
}