#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 55
#define INF 0x3f3f3f3f

int n, m, s, t, k;
int adj[MAXN][MAXN];
int monster[MAXN][MAXN];
int dp[MAXN][MAXN];

void dijkstra(int start) {
    memset(dp[start], INF, sizeof(dp[start]));
    dp[start][start] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dp[start][j] > dp[start][i] + adj[i][j]) {
                dp[start][j] = dp[start][i] + adj[i][j];
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &k);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u - 1][v - 1] = adj[v - 1][u - 1] = w;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!adj[i][j]) adj[i][j] = INF;
        }
    }

    dijkstra(s - 1);

    if (dp[s - 1][t - 1] >= k) {
        printf("IMP0SSBLE!!\n");
        return 0;
    }

    int min_blood = k - dp[s - 1][t - 1];
    for (int a = 0; a < n; ++a) {
        for (int b = 0; b < n; ++b) {
            if (monster[a][b] == 1 && dp[s - 1][a] + dp[b][t - 1] <= k) {
                min_blood = fmin(min_blood, max(k - dp[s - 1][a] - dp[b][t - 1], monster[a][b]));
            }
        }
    }

    printf("%d\n", min_blood);
    return 0;
}