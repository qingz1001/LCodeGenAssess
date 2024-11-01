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

int solve() {
    int result = 0;
    int all = (1 << n) - 1;

    for (int mask = 1; mask <= all; mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (mask == (1 << i)) {
                    dp[mask][i] = 0;
                } else {
                    for (int j = 0; j < n; j++) {
                        if (i != j && (mask & (1 << j))) {
                            dp[mask][i] = max(dp[mask][i], dp[mask ^ (1 << i)][j] + graph[j][i]);
                        }
                    }
                }
                result = max(result, dp[mask][i]);
            }
        }
    }

    return result;
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

    int ans = solve();
    printf("%d\n", ans);

    return 0;
}