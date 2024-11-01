#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_M 50

int n, m;
int graph[MAX_N][MAX_N];
int dp[1 << MAX_N][MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);

    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;
        graph[u][v] = graph[v][u] = w;
    }

    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 0;
    }

    int max_length = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                if (graph[u][v] == 0) continue;
                int new_mask = mask | (1 << v);
                dp[new_mask][v] = max(dp[new_mask][v], dp[mask][u] + graph[u][v]);
                max_length = max(max_length, dp[new_mask][v]);
            }
        }
    }

    printf("%d\n", max_length);
    return 0;
}