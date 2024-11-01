#include <stdio.h>
#include <stdlib.h>

#define MAXN 2005
#define INF 1000000 * 2000

int dp[MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int times[M][N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &times[i][j]);
        }
    }

    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= N; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for (int j = 0; j < N; j++) {
        for (int i = 1; i <= M; i++) {
            dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j] + times[i - 1][j]);
            if (i != M) {
                dp[i][j + 1] = min(dp[i][j + 1], dp[i + 1][j] + times[i - 1][j]);
            }
        }
    }

    int result = INF;
    for (int i = 1; i <= M; i++) {
        result = min(result, dp[i][N]);
    }

    printf("%d\n", result);

    return 0;
}