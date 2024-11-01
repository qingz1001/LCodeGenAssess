#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 10005
#define MAX_M 25
#define MAX_JUMP 6

int n, m, cost1, cost2;
int map[MAX_M][MAX_N];
int dp[MAX_M][MAX_N][MAX_JUMP];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &cost1, &cost2);
    
    for (int i = m; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &map[i][j]);
        }
    }
    
    memset(dp, -0x3f, sizeof(dp));
    dp[1][1][1] = map[1][1];
    
    int max_score = INT_MIN;
    int min_jumps = 5;
    int min_height = 5;
    
    for (int height = 1; height <= 5; height++) {
        for (int jumps = 1; jumps <= 5; jumps++) {
            memset(dp, -0x3f, sizeof(dp));
            dp[1][1][jumps] = map[1][1] - cost1 * (height - 1) - cost2 * (jumps - 1);
            
            for (int j = 1; j <= n; j++) {
                for (int i = 1; i <= m; i++) {
                    if (map[i][j] == -1) continue;
                    
                    for (int k = 1; k <= jumps; k++) {
                        // 不跳
                        if (j > 1) dp[i][j][jumps] = max(dp[i][j][jumps], dp[i][j-1][jumps]);
                        
                        // 跳跃
                        for (int h = 1; h <= height; h++) {
                            if (i + h <= m && j + h <= n) {
                                dp[i+h][j+h][jumps] = max(dp[i+h][j+h][jumps], dp[i][j][k] + map[i+h][j+h]);
                            }
                            if (i - h >= 1 && j + h <= n) {
                                dp[i-h][j+h][jumps] = max(dp[i-h][j+h][jumps], dp[i][j][k] + map[i-h][j+h]);
                            }
                        }
                        
                        // 连跳
                        if (k < jumps) {
                            for (int h = 1; h <= height; h++) {
                                if (i + h <= m && j + h <= n) {
                                    dp[i+h][j+h][k+1] = max(dp[i+h][j+h][k+1], dp[i][j][k] + map[i+h][j+h]);
                                }
                                if (i - h >= 1 && j + h <= n) {
                                    dp[i-h][j+h][k+1] = max(dp[i-h][j+h][k+1], dp[i][j][k] + map[i-h][j+h]);
                                }
                            }
                        }
                    }
                }
            }
            
            int current_max = -0x3f3f3f3f;
            for (int i = 1; i <= m; i++) {
                for (int k = 1; k <= jumps; k++) {
                    current_max = max(current_max, dp[i][n][k]);
                }
            }
            
            if (current_max > max_score) {
                max_score = current_max;
                min_jumps = jumps;
                min_height = height;
            } else if (current_max == max_score) {
                if (jumps < min_jumps || (jumps == min_jumps && height < min_height)) {
                    min_jumps = jumps;
                    min_height = height;
                }
            }
        }
    }
    
    if (max_score < 0) {
        printf("mission failed\n");
    } else {
        printf("%d %d %d\n", max_score, min_jumps, min_height);
    }
    
    return 0;
}