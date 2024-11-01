#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // Initialize the adjacency matrix for the bipartite graph
    int adj[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }

    // Process each group of edges
    for (int i = 0; i < m; i++) {
        int t;
        scanf("%d", &t);
        if (t == 0) {
            int a1, b1;
            scanf("%d %d", &a1, &b1);
            adj[a1 - 1][b1 - 1] = 1;
        } else if (t == 1) {
            int a1, b1, a2, b2;
            scanf("%d %d %d %d", &a1, &b1, &a2, &b2);
            adj[a1 - 1][b1 - 1] = 1;
            adj[a2 - 1][b2 - 1] = 1;
        } else if (t == 2) {
            int a1, b1, a2, b2;
            scanf("%d %d %d %d", &a1, &b1, &a2, &b2);
            adj[a1 - 1][b1 - 1] = 1;
            adj[a2 - 1][b2 - 1] = 1;
        }
    }

    // Calculate the expected number of perfect matchings
    long long dp[1 << n];
    for (int i = 0; i < (1 << n); i++) {
        dp[i] = 0;
    }
    dp[0] = 1;

    for (int s = 0; s < (1 << n); s++) {
        for (int u = 0; u < n; u++) {
            if (!(s & (1 << u))) continue;
            for (int v = 0; v < n; v++) {
                if (!(s & (1 << v)) || adj[u][v] == 0) continue;
                dp[s | (1 << v)] += dp[s ^ (1 << u)];
                dp[s | (1 << v)] %= MOD;
            }
        }
    }

    // Output the result
    printf("%lld\n", dp[(1 << n) - 1]);

    return 0;
}