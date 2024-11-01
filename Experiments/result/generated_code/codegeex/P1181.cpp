#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int segmentCount = 0;
    int currentSum = 0;

    for (int i = 0; i < N; i++) {
        if (currentSum + A[i] <= M) {
            currentSum += A[i];
        } else {
            segmentCount++;
            currentSum = A[i];
        }
    }

    segmentCount++; // 最后一段也要计算在内

    printf("%d\n", segmentCount);
    return 0;
}