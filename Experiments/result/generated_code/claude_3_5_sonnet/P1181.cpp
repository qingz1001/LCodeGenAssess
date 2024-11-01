#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int main() {
    int N, M;
    int A[MAX_N];
    int count = 1;
    long long sum = 0;

    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < N; i++) {
        if (sum + A[i] > M) {
            count++;
            sum = A[i];
        } else {
            sum += A[i];
        }
    }

    printf("%d\n", count);

    return 0;
}