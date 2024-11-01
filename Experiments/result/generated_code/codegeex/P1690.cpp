#include <stdio.h>
#include <limits.h>

int main() {
    int n, p;
    scanf("%d", &n);
    
    int dist[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }
    
    scanf("%d", &p);
    
    int treasures[p];
    for (int i = 0; i < p; i++) {
        scanf("%d", &treasures[i]);
        treasures[i]--;
    }
    
    // Initialize the dp array
    long long dp[1 << p][p];
    for (int mask = 0; mask < (1 << p); mask++) {
        for (int i = 0; i < p; i++) {
            dp[mask][i] = LLONG_MAX;
        }
    }
    
    // Base case: starting from the first treasure
    dp[1][0] = 0;
    
    // Fill the dp array
    for (int mask = 1; mask < (1 << p); mask++) {
        for (int i = 0; i < p; i++) {
            if (dp[mask][i] == LLONG_MAX) continue;
            for (int j = 0; j < p; j++) {
                if (mask & (1 << j)) continue;
                dp[mask | (1 << j)][j] = (dp[mask | (1 << j)][j] < dp[mask][i] + dist[treasures[i]][treasures[j]]) ? dp[mask | (1 << j)][j] : dp[mask][i] + dist[treasures[i]][treasures[j]];
            }
        }
    }
    
    // Find the minimum distance to reach the last treasure
    long long min_distance = LLONG_MAX;
    for (int i = 0; i < p; i++) {
        min_distance = (min_distance < dp[(1 << p) - 1][i] + dist[treasures[i]][n-1]) ? min_distance : dp[(1 << p) - 1][i] + dist[treasures[i]][n-1];
    }
    
    printf("%lld\n", min_distance);
    
    return 0;
}