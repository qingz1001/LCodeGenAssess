#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 500005

int n, m;
int price[MAXN];
int graph[MAXN][MAXN];
int dp[MAXN][MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dp[i][j] = 0;
            else dp[i][j] = price[j] - price[i];
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dp[i][k] != INT_MAX && dp[k][j] != INT_MAX) {
                    dp[i][j] = dp[i][j] > dp[i][k] + dp[k][j] ? dp[i][k] + dp[k][j] : dp[i][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = INT_MAX;
        }
    }

    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        if (z == 1) {
            graph[x][y] = 0;
        } else {
            graph[x][y] = 0;
            graph[y][x] = 0;
        }
    }

    dijkstra(1);

    int max_profit = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dp[1][i] != INT_MAX && dp[j][n] != INT_MAX) {
                max_profit = max_profit > dp[1][i] + dp[j][n] ? max_profit : dp[1][i] + dp[j][n];
            }
        }
    }

    printf("%d\n", max_profit);

    return 0;
}