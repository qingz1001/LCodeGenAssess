#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int count = 0;
    int current_sum = 0;
    for (int i = 0; i < N; i++) {
        current_sum += A[i];
        if (current_sum > M) {
            count++;
            current_sum = A[i];
        }
    }
    count++;

    printf("%d\n", count);
    return 0;
}