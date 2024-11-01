#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    int *A = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int min_diff = INT_MAX;

    for (int L = 0; L < N - 1; L++) {
        int max_val = A[L];
        int min_val = A[L];
        for (int R = L + 1; R < N; R++) {
            max_val = max(max_val, A[R]);
            min_val = min(min_val, A[R]);
            min_diff = min(min_diff, max_val - min_val);
        }
    }

    printf("%d\n", min_diff);

    free(A);
    return 0;
}