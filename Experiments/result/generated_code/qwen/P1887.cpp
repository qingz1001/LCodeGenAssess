#include <stdio.h>

int main() {
    long long N, M;
    scanf("%lld %lld", &N, &M);

    // Initialize the result array with the smallest possible values
    long long result[M];
    for (long long i = 0; i < M; i++) {
        result[i] = N / M + (i < N % M);
    }

    // Print the result in ascending order
    for (long long i = 0; i < M; i++) {
        printf("%lld ", result[i]);
    }
    printf("\n");

    return 0;
}