#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_B 500

int min(int a, int b) {
    return a < b ? a : b;
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

    int dp[MAX_B][1 << B];
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < (1 << B); j++) {
            dp[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < B; i++) {
        dp[i][1 << i] = A;
    }

    for (int mask = 1; mask < (1 << B); mask++) {
        for (int i = 0; i < B; i++) {
            if (!(mask & (1 << i))) continue;
            for (int j = 0; j < B; j++) {
                if (mask & (1 << j)) continue;
                if (K[i][j] == 0) continue;
                dp[j][mask | (1 << j)] = min(dp[j][mask | (1 << j)], dp[i][mask] + K[i][j]);
            }
        }
    }

    int result = INT_MAX;
    for (int i = 0; i < B; i++) {
        result = min(result, dp[i][(1 << B) - 1]);
    }

    printf("%d\n", result);

    return 0;
}