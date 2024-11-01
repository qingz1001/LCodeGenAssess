#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);

    // Initialize the adjacency matrix
    int **adj = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 1; i <= n; i++) {
        adj[i] = (int *)calloc(n + 1, sizeof(int));
    }

    // Read the dislikes
    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a][b] = 1;
        adj[b][a] = 1;
    }

    // Initialize the DP table
    long long dp[n + 1][n + 1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = 0;
        }
    }
    dp[1][1] = 1;

    // Fill the DP table
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (abs(j - 1) <= p && !adj[j][1]) {
                dp[i][j] = (dp[i][j] + dp[i - 1][1]) % MOD;
            }
            for (int l = 1; l <= n; l++) {
                if (abs(l - j) <= p && !adj[l][j]) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][l]) % MOD;
                }
            }
        }
    }

    // Output the result
    printf("%lld\n", dp[n][n]);

    // Free the memory
    for (int i = 1; i <= n; i++) {
        free(adj[i]);
    }
    free(adj);

    return 0;
}