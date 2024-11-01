#include <stdio.h>
#include <stdlib.h>

void merge(int N, int *A, int *B, int *result) {
    int i = 0, j = 0, k = 0;
    while (i < N && j < N && k < N) {
        if (A[i] + B[j] <= A[i + 1] + B[j + 1]) {
            result[k++] = A[i++] + B[j];
        } else {
            result[k++] = A[i] + B[j++];
        }
    }
    while (i < N && k < N) {
        result[k++] = A[i++] + B[j];
    }
    while (j < N && k < N) {
        result[k++] = A[i] + B[j++];
    }
}

int main() {
    int N;
    scanf("%d", &N);
    int A[N], B[N], result[2 * N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }
    merge(N, A, B, result);
    for (int i = 0; i < N; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}