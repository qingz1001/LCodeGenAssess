#include <stdio.h>
#include <string.h>

#define MAXN 101
#define MAXM 101

int n, m, k, x, y;
int police[MAXN][MAXM];
int dp[MAXN][MAXM][4];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    scanf("%d %d", &x, &y);

    memset(police, 0, sizeof(police));
    int p;
    scanf("%d", &p);
    for (int i = 0; i < p; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        police[a][b] = 1;
    }

    memset(dp, 0, sizeof(dp));
    dp[n][1][0] = 1;

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            if (police[i][j]) continue;
            for (int d = 0; d < 4; d++) {
                if (i < n) dp[i][j][d] = (dp[i][j][d] + dp[i+1][j][d]) % k;
                if (j > 1) dp[i][j][d] = (dp[i][j][d] + dp[i][j-1][(d+3)%4]) % k;
                if (d < 3) dp[i][j][d+1] = (dp[i][j][d+1] + dp[i][j][d]) % k;
            }
        }
    }

    int result = 0;
    for (int d = 0; d < 4; d++) {
        result = (result + dp[x][y][d]) % k;
    }

    printf("%d\n", result);

    return 0;
}