#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define MAX_P 10

int n, p;
int dist[MAX_N][MAX_N];
int treasure[MAX_P];
int dp[1 << MAX_P][MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }
    
    scanf("%d", &p);
    for (int i = 0; i < p; i++) {
        scanf("%d", &treasure[i]);
        treasure[i]--;  // 将区域编号转换为 0-based
    }
    
    memset(dp, 0x3f, sizeof(dp));  // 初始化为一个很大的值
    dp[0][0] = 0;  // 起点为 1 号区域
    
    for (int mask = 0; mask < (1 << p); mask++) {
        for (int i = 0; i < n; i++) {
            if (dp[mask][i] == 0x3f3f3f3f) continue;
            
            for (int j = 0; j < p; j++) {
                if (mask & (1 << j)) continue;
                
                int next_mask = mask | (1 << j);
                int next = treasure[j];
                dp[next_mask][next] = min(dp[next_mask][next], dp[mask][i] + dist[i][next]);
            }
        }
    }
    
    int result = INT_MAX;
    for (int mask = 0; mask < (1 << p); mask++) {
        result = min(result, dp[mask][n-1]);
    }
    
    printf("%d\n", result);
    
    return 0;
}