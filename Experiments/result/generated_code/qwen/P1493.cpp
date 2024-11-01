#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int A;
    int B;
} Pear;

int compare(const void *a, const void *b) {
    Pear *p1 = (Pear *)a;
    Pear *p2 = (Pear *)b;
    return p1->A * 3 + p1->B - (p2->A * 3 + p2->B);
}

int main() {
    int N, C1, C2, C3;
    scanf("%d", &N);
    scanf("%d %d %d", &C1, &C2, &C3);

    Pear pears[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &pears[i].A, &pears[i].B);
    }

    qsort(pears, N, sizeof(Pear), compare);

    int max_count = 0;
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += pears[i].A * C1 + pears[i].B * C2;
        if (sum <= C3) {
            max_count++;
        } else {
            break;
        }
    }

    printf("%d\n", max_count);

    return 0;
}