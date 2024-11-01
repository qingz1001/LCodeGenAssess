#include <stdio.h>
#include <stdlib.h>

#define MAXN 2005
#define INF 0x3f3f3f3f

int dp[MAXN][MAXN];

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int times[M][N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &times[i][j]);
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = INF;
        }
    }

    for (int i = 0; i < M; i++) {
        dp[i][0] = times[i][0];
    }

    for (int j = 1; j < N; j++) {
        for (int i = 0; i < M; i++) {
            for (int k = 0; k < M; k++) {
                if ((k == i - 1 || k == i) && dp[k][j - 1] != INF) {
                    dp[i][j] = fmin(dp[i][j], dp[k][j - 1] + times[i][j]);
                }
            }
        }
    }

    int min_time = INF;
    for (int i = 0; i < M; i++) {
        min_time = fmin(min_time, dp[i][N - 1]);
    }

    printf("%d\n", min_time);

    return 0;
}