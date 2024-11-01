#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int segments = 0;
    int current_sum = 0;

    for (int i = 0; i < N; i++) {
        if (current_sum + A[i] <= M) {
            current_sum += A[i];
        } else {
            segments++;
            current_sum = A[i];
        }
    }

    if (current_sum > 0) {
        segments++;
    }

    printf("%d\n", segments);

    return 0;
}