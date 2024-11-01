#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int total = 0;
    for (int i = 0; i < N; i++) {
        total += A[i];
    }
    int target = total / N;

    int moves = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] > target) {
            moves += A[i] - target;
        }
    }

    printf("%d\n", moves);

    return 0;
}