#include <stdio.h>
#include <stdlib.h>

#define MAXN 1501
#define INF -1e9

int dp[MAXN];

void dijkstra(int n, int edges[][3], int m) {
    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
    }
    dp[1] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];
            if (dp[u] != INF && dp[v] < dp[u] + w) {
                dp[v] = dp[u] + w;
            }
        }
    }

    if (dp[n] == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", dp[n]);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int edges[m][3];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    }
    dijkstra(n, edges, m);
    return 0;
}