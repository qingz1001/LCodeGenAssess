#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int canPartition(int* A, int N, int M, long long maxSum) {
    long long currentSum = 0;
    int segments = 1;
    for (int i = 0; i < N; i++) {
        if (currentSum + A[i] > maxSum) {
            segments++;
            currentSum = A[i];
            if (segments > M) return 0;
        } else {
            currentSum += A[i];
        }
    }
    return 1;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int* A = (int*)malloc(N * sizeof(int));
    long long sum = 0;
    int maxElement = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        sum += A[i];
        if (A[i] > maxElement) maxElement = A[i];
    }

    long long left = maxElement;
    long long right = sum;
    long long result = right;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (canPartition(A, N, M, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%lld\n", result);
    free(A);
    return 0;
}