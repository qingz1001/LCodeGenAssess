#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 10001
#define MAX_M 21
#define MAX_JUMP 5

int n, m, cost1, cost2;
int map[MAX_M][MAX_N];
long long dp[MAX_M][MAX_N][MAX_JUMP + 1];

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &cost1, &cost2);
    
    for (int i = m; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &map[i][j]);
        }
    }
    
    memset(dp, -1, sizeof(dp));
    dp[1][1][1] = map[1][1];
    
    long long max_score = -1;
    int min_jumps = 6, min_height = 21;
    
    for (int height = 1; height <= m; height++) {
        for (int jumps = 1; jumps <= 5; jumps++) {
            long long cost = (height - 1) * cost1 + (jumps - 1) * cost2;
            
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dp[i][j][jumps] == -1) continue;
                    
                    for (int k = 1; k <= height && j + k <= n; k++) {
                        int new_i = i + k > m ? m * 2 - i - k : i + k;
                        if (new_i < 1 || map[new_i][j + k] == -1) break;
                        
                        dp[new_i][j + k][jumps] = max(dp[new_i][j + k][jumps], dp[i][j][jumps] + map[new_i][j + k]);
                        
                        if (j + k == n && dp[new_i][j + k][jumps] - cost > max_score) {
                            max_score = dp[new_i][j + k][jumps] - cost;
                            min_jumps = jumps;
                            min_height = height;
                        } else if (j + k == n && dp[new_i][j + k][jumps] - cost == max_score) {
                            if (jumps < min_jumps || (jumps == min_jumps && height < min_height)) {
                                min_jumps = jumps;
                                min_height = height;
                            }
                        }
                        
                        for (int l = 1; l < jumps && j + k + l <= n; l++) {
                            int next_i = new_i - l < 1 ? l - new_i + 2 : new_i - l;
                            if (next_i > m || map[next_i][j + k + l] == -1) break;
                            
                            dp[next_i][j + k + l][jumps] = max(dp[next_i][j + k + l][jumps], dp[new_i][j + k][jumps] + map[next_i][j + k + l]);
                            
                            if (j + k + l == n && dp[next_i][j + k + l][jumps] - cost > max_score) {
                                max_score = dp[next_i][j + k + l][jumps] - cost;
                                min_jumps = jumps;
                                min_height = height;
                            } else if (j + k + l == n && dp[next_i][j + k + l][jumps] - cost == max_score) {
                                if (jumps < min_jumps || (jumps == min_jumps && height < min_height)) {
                                    min_jumps = jumps;
                                    min_height = height;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (max_score == -1) {
        printf("mission failed\n");
    } else {
        printf("%lld %d %d\n", max_score, min_jumps, min_height);
    }
    
    return 0;
}