#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100000

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N;
    int A[MAX_N];
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int result = INT_MAX;
    int minVal = A[0], maxVal = A[0];

    for (int i = 1; i < N; i++) {
        minVal = min(minVal, A[i]);
        maxVal = max(maxVal, A[i]);
        result = min(result, maxVal - minVal);
    }

    printf("%d\n", result);

    return 0;
}