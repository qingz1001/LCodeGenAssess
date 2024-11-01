#include <stdio.h>
#include <stdlib.h>

#define MAX_B 500
#define MAX_A 1000

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int A, B;
    scanf("%d %d", &A, &B);

    int K[MAX_B][MAX_B];
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
            scanf("%d", &K[i][j]);
        }
    }

    int dp[B][B];
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
            if (i == j) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = A + A; // Initialize with the cost of buying two items without any discount
            }
        }
    }

    for (int k = 0; k < B; k++) {
        for (int i = 0; i < B; i++) {
            for (int j = 0; j < B; j++) {
                if (i != j && i != k && j != k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + (K[i][k] + K[k][j]));
                }
            }
        }
    }

    int result = A * B;
    for (int i = 0; i < B; i++) {
        result = min(result, dp[0][i] + A);
    }

    printf("%d\n", result);

    return 0;
}