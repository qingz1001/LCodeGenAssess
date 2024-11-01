#include <stdio.h>
#include <stdlib.h>

#define MAXN 120

int max(int a, int b) {
    return (a > b) ? a : b;
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
        int temp[n];
        for (int i = 0; i < n; i++) {
            temp[i] = 0;
        }
        for (int right = left; right < n; right++) {
            for (int i = 0; i < n; i++) {
                temp[i] += matrix[i][right];
            }
            int currentSum = 0, minSum = 0;
            for (int i = 0; i < n; i++) {
                currentSum += temp[i];
                if (currentSum - minSum > maxSum) {
                    maxSum = currentSum - minSum;
                }
                if (currentSum < minSum) {
                    minSum = currentSum;
                }
            }
        }
    }

    printf("%d\n", maxSum);
    return 0;
}