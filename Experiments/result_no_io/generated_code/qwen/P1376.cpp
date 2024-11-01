#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10001
#define MAX_C 5001
#define MAX_S 101
#define MAX_Y 10001

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int N, S;
    scanf("%d %d", &N, &S);
    int C[MAX_N], Y[MAX_N];
    for (int i = 1; i <= N; i++) {
        scanf("%d %d", &C[i], &Y[i]);
    }

    int dp[MAX_N][MAX_Y + 1];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= MAX_Y; j++) {
            dp[i][j] = 0x3f3f3f3f;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= MAX_Y; j++) {
            if (dp[i - 1][j] != 0x3f3f3f3f) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + C[i]);
                dp[i][min(j + Y[i], MAX_Y)] = min(dp[i][min(j + Y[i], MAX_Y)], dp[i - 1][j]);
                dp[i][max(0, j - 1)] = min(dp[i][max(0, j - 1)], dp[i - 1][j] + S);
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= MAX_Y; i++) {
        ans = min(ans, dp[N][i]);
    }

    printf("%d\n", ans);

    return 0;
}