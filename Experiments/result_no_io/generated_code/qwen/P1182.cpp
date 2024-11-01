#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int canDivide(int* A, int N, int M, int mid) {
    int count = 1;
    int sum = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] > mid) {
            return 0;
        }
        if (sum + A[i] > mid) {
            count++;
            sum = A[i];
        } else {
            sum += A[i];
        }
    }
    return count <= M;
}

int findMinMaxSum(int* A, int N, int M) {
    int left = 0;
    int right = 0;
    for (int i = 0; i < N; i++) {
        right += A[i];
    }
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (canDivide(A, N, M, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int* A = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    printf("%d\n", findMinMaxSum(A, N, M));
    free(A);
    return 0;
}