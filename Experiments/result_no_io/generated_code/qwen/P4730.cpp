#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 0x3f3f3f3f

int n, m;
int d_min, d_max;
int points[MAXN][2];
int moves[MAXN][MAXN], move_cnt[MAXN];
int attacks[MAXN][2];
int dp[MAXN][MAXN];

void bfs(int start, int end) {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = INF;
        }
    }
    dp[start][start] = 0;
    int queue[MAXN * MAXN], front = 0, rear = 0;
    queue[rear++] = start;
    while (front != rear) {
        int u = queue[front++];
        for (int v = 0; v <= n; ++v) {
            if (moves[u][v] && dp[u][v] > dp[u][u] + 1) {
                dp[u][v] = dp[u][u] + 1;
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%d %d", &d_min, &d_max);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &points[i][0], &points[i][1]);
    }
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        scanf("%d %d", &attacks[i][0], &attacks[i][1]);
    }
    for (int i = 0; i < m; ++i) {
        int a, b, type;
        scanf("%d %d %d", &a, &b, &type);
        if (type == 0) {
            moves[a][b] = 1;
            moves[b][a] = 1;
        } else {
            moves[n + a][n + b] = 1;
            moves[n + b][n + a] = 1;
        }
    }
    for (int i = 1; i <= n; ++i) {
        bfs(i, i);
    }
    for (int i = 0; i < k; ++i) {
        int ans = INF;
        for (int j = 1; j <= n; ++j) {
            if (dp[j][attacks[i][0]] < INF && dp[j][attacks[i][1]] < INF) {
                ans = fmin(ans, dp[j][attacks[i][0]] + dp[j][attacks[i][1]]);
            }
        }
        printf("%d\n", ans == INF ? -1 : ans);
    }
    return 0;
}