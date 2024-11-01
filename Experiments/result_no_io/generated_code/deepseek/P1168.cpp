#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N;
    scanf("%d", &N);
    int *A = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    for (int i = 1; i <= (N + 1) / 2; i++) {
        qsort(A, 2 * i - 1, sizeof(int), compare);
        printf("%d\n", A[(2 * i - 1) / 2]);
    }

    free(A);
    return 0;
}