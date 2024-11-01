#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 200005

typedef struct {
    int to, weight;
} Edge;

int n, m, k, p;
Edge edges[MAXM];
int dist[MAXN], dp[MAXN][MAXK + 1];

void dijkstra(int start) {
    for (int i = 1; i <= n; ++i) dist[i] = INT_MAX;
    dist[start] = 0;
    dp[start][0] = 1;
    for (int i = 1; i <= n; ++i) {
        int u = -1, min_dist = INT_MAX;
        for (int j = 1; j <= n; ++j) {
            if (dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        for (int j = 0; j <= k; ++j) {
            dp[u][j] %= p;
        }
        for (int j = 0; j < m; ++j) {
            if (edges[j].to == u) continue;
            int v = edges[j].to, w = edges[j].weight;
            if (min_dist + w < dist[v]) {
                dist[v] = min_dist + w;
                for (int j = 0; j <= k; ++j) {
                    dp[v][j] = dp[u][j];
                }
            } else if (min_dist + w == dist[v]) {
                for (int j = 0; j <= k; ++j) {
                    dp[v][(j + w) % (k + 1)] += dp[u][j];
                    dp[v][(j + w) % (k + 1)] %= p;
                }
            }
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d", &n, &m, &k, &p);
        for (int i = 0; i < m; ++i) {
            scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
        }
        dijkstra(1);
        int ans = 0;
        for (int i = 0; i <= k; ++i) {
            ans += dp[n][i];
            ans %= p;
        }
        if (ans == 0 && dist[n] != INT_MAX) {
            printf("-1\n");
        } else {
            printf("%d\n", ans);
        }
    }
    return 0;
}