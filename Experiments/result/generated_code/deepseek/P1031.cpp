#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    int total = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        total += A[i];
    }

    int average = total / N;
    int moves = 0;

    for (int i = 0; i < N - 1; i++) {
        if (A[i] != average) {
            A[i + 1] += A[i] - average;
            moves++;
        }
    }

    printf("%d\n", moves);
    return 0;
}