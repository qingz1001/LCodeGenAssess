#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int A;
    int B;
} Pear;

int comparePears(const void *a, const void *b) {
    Pear *p1 = (Pear *)a;
    Pear *p2 = (Pear *)b;
    return (p1->A - p2->A) + (p1->B - p2->B);
}

int main() {
    int N, C1, C2, C3;
    scanf("%d", &N);
    scanf("%d %d %d", &C1, &C2, &C3);

    Pear pears[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &pears[i].A, &pears[i].B);
    }

    qsort(pears, N, sizeof(Pear), comparePears);

    int maxCount = 0;
    for (int i = 0; i < N; i++) {
        int count = 0;
        int A0 = pears[i].A;
        int B0 = pears[i].B;
        for (int j = i; j < N; j++) {
            if (C1 * (pears[j].A - A0) + C2 * (pears[j].B - B0) <= C3) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
        }
    }

    printf("%d\n", maxCount);
    return 0;
}