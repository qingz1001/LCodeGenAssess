#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

typedef struct {
    int sum;
    int i;
    int j;
} Pair;

int compare(const void* a, const void* b) {
    return ((Pair*)a)->sum - ((Pair*)b)->sum;
}

int main() {
    int N;
    int A[MAX_N], B[MAX_N];
    Pair heap[MAX_N];
    int used[MAX_N] = {0};

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }

    for (int i = 0; i < N; i++) {
        heap[i].sum = A[i] + B[0];
        heap[i].i = i;
        heap[i].j = 0;
    }

    qsort(heap, N, sizeof(Pair), compare);

    for (int k = 0; k < N; k++) {
        printf("%d ", heap[0].sum);

        int i = heap[0].i;
        int j = heap[0].j;

        if (j + 1 < N) {
            heap[0].sum = A[i] + B[j + 1];
            heap[0].j = j + 1;
            qsort(heap, N, sizeof(Pair), compare);
        }
    }

    return 0;
}