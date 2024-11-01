#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int A;
    int B;
} Pear;

int compare(const void *a, const void *b) {
    Pear *pearA = (Pear *)a;
    Pear *pearB = (Pear *)b;
    if (pearA->A == pearB->A) {
        return pearA->B - pearB->B;
    }
    return pearA->A - pearB->A;
}

int main() {
    int N;
    scanf("%d", &N);
    Pear pears[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &pears[i].A, &pears[i].B);
    }
    int C1, C2, C3;
    scanf("%d %d %d", &C1, &C2, &C3);

    qsort(pears, N, sizeof(Pear), compare);

    int left = 0, right = 0;
    int maxCount = 0;
    while (right < N) {
        while (right < N && (C1 * (pears[right].A - pears[left].A) + C2 * (pears[right].B - pears[left].B) <= C3)) {
            right++;
        }
        maxCount = (right - left) > maxCount ? (right - left) : maxCount;
        left++;
    }

    printf("%d\n", maxCount);
    return 0;
}