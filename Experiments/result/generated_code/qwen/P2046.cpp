#include <stdio.h>
#include <stdlib.h>

#define MAXN 501

int n;
long long flow[MAXN][MAXN][4];
long long dp[MAXN][MAXN];

void dijkstra() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = (i == 0 && j == 0) ? 0 : 1e18;
        }
    }

    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int k = 0; k < 4 * n * (n + 1); k++) {
        int x = k / (2 * n + 2);
        int y = (k % (2 * n + 2)) / 2;
        int dir = k % 2;

        if (x > 0) {
            dp[x][y] = dp[x - 1][y] + flow[x][y][dir];
        }
        if (y > 0) {
            dp[x][y] = dp[x][y - 1] + flow[x][y][dir];
        }
        if (x < n) {
            dp[x][y] = dp[x + 1][y] + flow[x][y][dir];
        }
        if (y < n) {
            dp[x][y] = dp[x][y + 1] + flow[x][y][dir];
        }
    }

    printf("%lld\n", dp[n][n]);
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n * (n + 1); i++) {
        scanf("%lld", &flow[0][i][0]);
    }
    for (int i = 0; i < n * (n + 1); i++) {
        scanf("%lld", &flow[i][0][1]);
    }
    for (int i = 0; i < n * (n + 1); i++) {
        scanf("%lld", &flow[n][i][2]);
    }
    for (int i = 0; i < n * (n + 1); i++) {
        scanf("%lld", &flow[i][n][3]);
    }

    dijkstra();

    return 0;
}