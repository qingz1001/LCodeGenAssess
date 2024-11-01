#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 105

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N;
    int beads[MAXN * 2];
    int dp[MAXN * 2][MAXN * 2];

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &beads[i]);
        beads[N + i] = beads[i];
    }

    for (int len = 2; len <= N; len++) {
        for (int i = 0; i < 2 * N - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = 0;
            for (int k = i; k < j; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + beads[i] * beads[k + 1] * beads[j + 1]);
            }
        }
    }

    int max_energy = 0;
    for (int i = 0; i < N; i++) {
        max_energy = max(max_energy, dp[i][i + N - 1]);
    }

    printf("%d\n", max_energy);

    return 0;
}