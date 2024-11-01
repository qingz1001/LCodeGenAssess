#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 101
#define MAX_M 21
#define INF 0x3f3f3f3f

int n, m, k, e;
int graph[MAX_M][MAX_M];
int dist[MAX_M][MAX_M];
int blocked[MAX_M][MAX_N];

void floyd() {
    for (int k = 1; k <= m; k++) {
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int dp[MAX_N][MAX_M];

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &e);

    memset(graph, 0x3f, sizeof(graph));
    memset(dist, 0x3f, sizeof(dist));

    for (int i = 1; i <= m; i++) {
        graph[i][i] = dist[i][i] = 0;
    }

    for (int i = 0; i < e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = graph[v][u] = w;
        dist[u][v] = dist[v][u] = w;
    }

    floyd();

    int d;
    scanf("%d", &d);
    for (int i = 0; i < d; i++) {
        int p, a, b;
        scanf("%d %d %d", &p, &a, &b);
        for (int j = a; j <= b; j++) {
            blocked[p][j] = 1;
        }
    }

    memset(dp, 0x3f, sizeof(dp));
    for (int j = 1; j <= m; j++) {
        if (!blocked[j][1]) {
            dp[1][j] = dist[1][j];
        }
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (blocked[j][i]) continue;
            for (int l = 1; l <= m; l++) {
                if (blocked[l][i-1]) continue;
                int cost = dp[i-1][l] + dist[l][j];
                if (l != j) cost += k;
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    int result = INF;
    for (int j = 1; j <= m; j++) {
        if (dp[n][j] + dist[j][m] < result) {
            result = dp[n][j] + dist[j][m];
        }
    }

    printf("%d\n", result);

    return 0;
}