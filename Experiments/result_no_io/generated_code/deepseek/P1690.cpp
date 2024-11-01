#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXP 10

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    
    int dist[MAXN][MAXN];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &dist[i][j]);
        }
    }
    
    int P;
    scanf("%d", &P);
    
    int treasures[MAXP];
    for (int i = 0; i < P; i++) {
        scanf("%d", &treasures[i]);
        treasures[i]--; // Convert to 0-based index
    }
    
    // Floyd-Warshall algorithm to find shortest paths between all pairs
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    // Dynamic Programming to find the shortest path visiting all treasures
    int dp[1 << MAXP][MAXP];
    for (int mask = 0; mask < (1 << P); mask++) {
        for (int i = 0; i < P; i++) {
            dp[mask][i] = INT_MAX;
        }
    }
    
    // Initialize starting point
    for (int i = 0; i < P; i++) {
        dp[1 << i][i] = dist[0][treasures[i]];
    }
    
    // Fill the DP table
    for (int mask = 1; mask < (1 << P); mask++) {
        for (int i = 0; i < P; i++) {
            if (mask & (1 << i)) {
                for (int j = 0; j < P; j++) {
                    if (!(mask & (1 << j))) {
                        int new_mask = mask | (1 << j);
                        if (dp[mask][i] != INT_MAX && dist[treasures[i]][treasures[j]] != INT_MAX) {
                            dp[new_mask][j] = min(dp[new_mask][j], dp[mask][i] + dist[treasures[i]][treasures[j]]);
                        }
                    }
                }
            }
        }
    }
    
    // Find the minimum distance to reach the last point
    int min_distance = INT_MAX;
    for (int i = 0; i < P; i++) {
        if (dp[(1 << P) - 1][i] != INT_MAX && dist[treasures[i]][N-1] != INT_MAX) {
            min_distance = min(min_distance, dp[(1 << P) - 1][i] + dist[treasures[i]][N-1]);
        }
    }
    
    printf("%d\n", min_distance);
    
    return 0;
}