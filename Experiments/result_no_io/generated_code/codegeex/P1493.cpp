#include <stdio.h>
#include <stdlib.h>

// 定义结构体表示梨子
typedef struct {
    int A;
    int B;
} Pear;

// 比较函数，用于qsort排序
int cmp(const void *a, const void *b) {
    Pear *pearA = (Pear *)a;
    Pear *pearB = (Pear *)b;
    if (pearA->A != pearB->A)
        return pearA->A - pearB->A;
    else
        return pearA->B - pearB->B;
}

int main() {
    int N, C1, C2, C3;
    scanf("%d %d %d %d", &N, &C1, &C2, &C3);

    Pear *pears = (Pear *)malloc(sizeof(Pear) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &pears[i].A, &pears[i].B);
    }

    // 按照A升序，B升序排序
    qsort(pears, N, sizeof(Pear), cmp);

    int maxCount = 0;
    int left = 0, right = 0;

    // 滑动窗口法
    while (right < N) {
        while (right < N && (C1 * (pears[right].A - pears[left].A) + C2 * (pears[right].B - pears[left].B) <= C3)) {
            right++;
        }
        if (right - left > maxCount) {
            maxCount = right - left;
        }
        left++;
    }

    printf("%d\n", maxCount);
    free(pears);
    return 0;
}