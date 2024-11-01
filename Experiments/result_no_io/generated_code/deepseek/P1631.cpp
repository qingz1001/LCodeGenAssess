#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

typedef struct {
    int sum;
    int idx;
} Pair;

int cmp(const void *a, const void *b) {
    return ((Pair *)a)->sum - ((Pair *)b)->sum;
}

int main() {
    int N;
    scanf("%d", &N);
    int A[MAXN], B[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }

    Pair pairs[MAXN];
    for (int i = 0; i < N; i++) {
        pairs[i].sum = A[i] + B[0];
        pairs[i].idx = 0;
    }

    qsort(pairs, N, sizeof(Pair), cmp);

    for (int k = 0; k < N; k++) {
        printf("%d ", pairs[0].sum);
        if (pairs[0].idx < N - 1) {
            pairs[0].sum = A[pairs[0].sum - B[pairs[0].idx]] + B[++pairs[0].idx];
        } else {
            pairs[0].sum = INT_MAX;
        }
        qsort(pairs, N, sizeof(Pair), cmp);
    }

    return 0;
}