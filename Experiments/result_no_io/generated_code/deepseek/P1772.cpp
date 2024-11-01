#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 105
#define MAXM 25
#define MAXE 205
#define INF INT_MAX

int n, m, k, e;
int graph[MAXM][MAXM];
int blocked[MAXM][MAXN];
int dp[MAXN];

void floyd_warshall(int days) {
    int dist[MAXM][MAXM];
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    for (int k = 1; k <= m; k++) {
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            if (dist[i][j] == INF) {
                graph[i][j] = INF;
            } else {
                graph[i][j] = dist[i][j] * days;
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &e);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 0; i < e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = graph[v][u] = w;
    }

    int d;
    scanf("%d", &d);
    for (int i = 0; i < d; i++) {
        int p, a, b;
        scanf("%d %d %d", &p, &a, &b);
        for (int j = a; j <= b; j++) {
            blocked[p][j] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int can_use[MAXM] = {0};
            for (int p = 1; p <= m; p++) {
                can_use[p] = 1;
                for (int day = i; day <= j; day++) {
                    if (blocked[p][day]) {
                        can_use[p] = 0;
                        break;
                    }
                }
            }

            floyd_warshall(j - i + 1);

            int cost = graph[1][m];
            if (cost != INF) {
                dp[j] = (dp[i - 1] + cost + k < dp[j]) ? dp[i - 1] + cost + k : dp[j];
            }
        }
    }

    printf("%d\n", dp[n] - k);

    return 0;
}