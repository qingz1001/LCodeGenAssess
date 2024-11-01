#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define INF 1000000000

typedef struct {
    int rmb;
    int rp;
    int time;
} MM;

MM mm[MAXN];
int dp[MAXN + 1][MAXN + 1][MAXN + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, m, r;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &mm[i].rmb, &mm[i].rp, &mm[i].time);
    }
    scanf("%d %d", &m, &r);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= r; k++) {
                dp[i][j][k] = INF;
            }
        }
    }

    dp[0][0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= r; k++) {
                if (dp[i][j][k] == INF) continue;
                dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k]);
                if (j + mm[i].rmb <= m && k + mm[i].rp <= r) {
                    dp[i + 1][j + mm[i].rmb][k + mm[i].rp] = min(dp[i + 1][j + mm[i].rmb][k + mm[i].rp], dp[i][j][k] + mm[i].time);
                }
            }
        }
    }

    int max_mm = 0;
    for (int j = 0; j <= m; j++) {
        for (int k = 0; k <= r; k++) {
            if (dp[n][j][k] != INF) {
                max_mm = max(max_mm, j);
            }
        }
    }

    int min_time = INF;
    for (int j = 0; j <= m; j++) {
        for (int k = 0; k <= r; k++) {
            if (dp[n][j][k] != INF && j == max_mm) {
                min_time = min(min_time, dp[n][j][k]);
            }
        }
    }

    printf("%d\n", min_time);

    return 0;
}