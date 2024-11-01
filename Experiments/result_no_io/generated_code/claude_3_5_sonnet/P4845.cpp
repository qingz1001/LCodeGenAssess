#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1005
#define MAX_K 1005
#define MAX_R 1005

int n, k, r;
int w[MAX_N];
int adj[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];
int dp[MAX_N][MAX_K];

void floyd_warshall() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int solve() {
    memset(dp, 0, sizeof(dp));
    
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] <= r) {
                sum += w[j];
            }
        }
        dp[i][1] = sum;
    }
    
    for (int j = 2; j <= k; j++) {
        for (int i = 1; i <= n; i++) {
            for (int p = 1; p < i; p++) {
                int sum = 0;
                for (int q = 1; q <= n; q++) {
                    if (dist[i][q] <= r && dist[p][q] > r) {
                        sum += w[q];
                    }
                }
                if (dp[p][j-1] + sum > dp[i][j]) {
                    dp[i][j] = dp[p][j-1] + sum;
                }
            }
        }
    }
    
    int max_val = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i][k] > max_val) {
            max_val = dp[i][k];
        }
    }
    
    return max_val;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d %d", &n, &k, &r);
        
        for (int i = 1; i <= n; i++) {
            scanf("%d", &w[i]);
        }
        
        memset(adj, 0, sizeof(adj));
        memset(dist, 0x3f, sizeof(dist));
        
        for (int i = 1; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            adj[x][y] = adj[y][x] = 1;
            dist[x][y] = dist[y][x] = 1;
        }
        
        for (int i = 1; i <= n; i++) {
            dist[i][i] = 0;
        }
        
        floyd_warshall();
        
        printf("%d\n", solve());
    }
    
    return 0;
}