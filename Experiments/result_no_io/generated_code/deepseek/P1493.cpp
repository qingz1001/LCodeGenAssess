#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000

typedef struct {
    int A;
    int B;
} Pear;

int comparePears(const void *a, const void *b) {
    Pear *pearA = (Pear *)a;
    Pear *pearB = (Pear *)b;
    return (pearA->A - pearB->A);
}

int main() {
    int N, C1, C2, C3;
    Pear pears[MAX_N];

    scanf("%d", &N);
    scanf("%d %d %d", &C1, &C2, &C3);

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
            int A_diff = pears[j].A - A0;
            int B_diff = pears[j].B - B0;
            if (C1 * A_diff + C2 * B_diff <= C3) {
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