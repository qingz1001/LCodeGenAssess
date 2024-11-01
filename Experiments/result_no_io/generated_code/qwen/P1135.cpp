#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int N, A, B;
    scanf("%d %d %d", &N, &A, &B);
    int K[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &K[i]);
    }

    if (A == B) {
        printf("0\n");
        return 0;
    }

    int dp[MAX_N][2] = {0};
    dp[A - 1][0] = 0; // 0: not visited, 1: visited
    dp[A - 1][1] = 1;

    for (int i = A; i <= N; i++) {
        dp[i - 1][0] = dp[i - 1][1] = -1;
    }

    for (int i = A + 1; i <= N; i++) {
        if (dp[i - K[i - 1] - 1][1] != -1 && i - K[i - 1] >= 1) {
            dp[i - 1][0] = min(dp[i - 1][0], dp[i - K[i - 1] - 1][1] + 1);
        }
        if (dp[i][1] != -1) {
            dp[i - 1][0] = min(dp[i - 1][0], dp[i][1] + 1);
        }
    }

    for (int i = B - 1; i >= 1; i--) {
        dp[i - 1][0] = dp[i - 1][1] = -1;
    }

    for (int i = B - 2; i >= 1; i--) {
        if (dp[i + K[i - 1]][1] != -1 && i + K[i - 1] <= N) {
            dp[i - 1][0] = min(dp[i - 1][0], dp[i + K[i - 1]][1] + 1);
        }
        if (dp[i][1] != -1) {
            dp[i - 1][0] = min(dp[i - 1][0], dp[i][1] + 1);
        }
    }

    printf("%d\n", dp[B - 1][0]);
    return 0;
}