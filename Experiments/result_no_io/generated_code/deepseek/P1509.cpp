#include <stdio.h>
#include <stdlib.h>

#define MAXN 101
#define INF 1000000

typedef struct {
    int rmb;
    int rp;
    int time;
} MM;

MM mm[MAXN];
int dp[MAXN][MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, m, r;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d %d", &mm[i].rmb, &mm[i].rp, &mm[i].time);
    }
    scanf("%d %d", &m, &r);

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= r; ++k) {
                dp[i][j][k] = INF;
            }
        }
    }

    dp[0][0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= r; ++k) {
                dp[i][j][k] = dp[i-1][j][k];
                if (j >= mm[i].rmb && k >= mm[i].rp) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i-1][j-mm[i].rmb][k-mm[i].rp] + mm[i].time);
                }
            }
        }
    }

    int max_mm = 0;
    int min_time = INF;

    for (int j = 0; j <= m; ++j) {
        for (int k = 0; k <= r; ++k) {
            if (dp[n][j][k] < INF) {
                int count = 0;
                int rmb_left = j;
                int rp_left = k;
                for (int i = n; i >= 1; --i) {
                    if (dp[i][rmb_left][rp_left] != dp[i-1][rmb_left][rp_left]) {
                        count++;
                        rmb_left -= mm[i].rmb;
                        rp_left -= mm[i].rp;
                    }
                }
                if (count > max_mm || (count == max_mm && dp[n][j][k] < min_time)) {
                    max_mm = count;
                    min_time = dp[n][j][k];
                }
            }
        }
    }

    printf("%d\n", min_time);

    return 0;
}