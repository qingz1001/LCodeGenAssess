#include <stdio.h>
#include <stdlib.h>

#define MAXN 120

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int matrix[MAXN][MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int maxSum = INT_MIN;
    for (int left = 0; left < n; left++) {
        int sum[MAXN] = {0};
        for (int right = left; right < n; right++) {
            for (int i = 0; i < n; i++) {
                sum[i] += matrix[i][right];
            }
            int currentMax = 0, currentMin = 0, currentSum = 0;
            for (int i = 0; i < n; i++) {
                if (sum[i] >= 0) {
                    currentSum += sum[i];
                    currentMax = max(currentMax, currentSum);
                } else {
                    if (currentSum + sum[i] <= 0) {
                        currentSum = 0;
                    } else {
                        currentSum += sum[i];
                        currentMax = max(currentMax, currentSum);
                    }
                }
                currentMin = min(currentMin, currentSum);
                maxSum = max(maxSum, currentMax - currentMin);
            }
        }
    }

    printf("%d\n", maxSum);
    return 0;
}