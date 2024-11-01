#include <stdio.h>
#include <stdlib.h>

void findMaxProduct(int N, int M) {
    int *result = (int *)malloc(M * sizeof(int));
    int quotient = N / M;
    int remainder = N % M;

    for (int i = 0; i < M; i++) {
        if (i < M - remainder) {
            result[i] = quotient;
        } else {
            result[i] = quotient + 1;
        }
    }

    for (int i = 0; i < M; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    findMaxProduct(N, M);
    return 0;
}