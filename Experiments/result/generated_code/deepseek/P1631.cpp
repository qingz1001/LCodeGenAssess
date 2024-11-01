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
        printf("%d", pairs[0].sum);
        if (k < N - 1) printf(" ");

        int i = pairs[0].idx + 1;
        if (i < N) {
            pairs[0].sum = A[pairs[0].sum - B[pairs[0].idx]] + B[i];
            pairs[0].idx = i;
        } else {
            pairs[0] = pairs[N - 1];
            N--;
        }

        int j = 0;
        while (j < N - 1 && pairs[j].sum > pairs[j + 1].sum) {
            Pair temp = pairs[j];
            pairs[j] = pairs[j + 1];
            pairs[j + 1] = temp;
            j++;
        }
    }

    printf("\n");
    return 0;
}