#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int A;
    int B;
} Pear;

int compare(const void *a, const void *b) {
    Pear p1 = *(Pear *)a;
    Pear p2 = *(Pear *)b;
    if (p1.A != p2.A) return p1.A - p2.A;
    return p1.B - p2.B;
}

int main() {
    int N;
    scanf("%d", &N);
    int C1, C2, C3;
    scanf("%d %d %d", &C1, &C2, &C3);

    Pear pears[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &pears[i].A, &pears[i].B);
    }

    qsort(pears, N, sizeof(Pear), compare);

    int max_count = 0;
    for (int i = 0; i < N; i++) {
        int count = 1;
        for (int j = i + 1; j < N; j++) {
            if (C1 * (pears[j].A - pears[i].A) + C2 * (pears[j].B - pears[i].B) <= C3) {
                count++;
            } else {
                break;
            }
        }
        if (count > max_count) {
            max_count = count;
        }
    }

    printf("%d\n", max_count);

    return 0;
}