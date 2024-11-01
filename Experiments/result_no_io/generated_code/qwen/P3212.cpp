#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20
#define MAX_A 1000
#define MAX_T 3

typedef struct {
    int type;
    int timeA;
    int timeB;
} Task;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    Task tasks[MAX_N];
    
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &tasks[i].type, &tasks[i].timeA, &tasks[i].timeB);
    }
    
    int dp[2][MAX_N + 1][MAX_A * MAX_T + 1];
    
    // Initialize DP table
    for (int j = 0; j <= n; ++j) {
        for (int k = 0; k <= MAX_A * MAX_T; ++k) {
            dp[0][j][k] = dp[1][j][k] = 1e9;
        }
    }
    dp[0][0][0] = dp[1][0][0] = 0;
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= MAX_A * MAX_T; ++k) {
                if (dp[0][j][k] == 1e9 || dp[1][j][k] == 1e9) continue;
                
                int machineA = (j == i) ? tasks[i - 1].timeA : 0;
                int machineB = (j == i) ? tasks[i - 1].timeB : 0;
                
                if (tasks[i - 1].type == 1) {
                    dp[0][j][k] = min(dp[0][j][k], dp[0][j][k]);
                    dp[1][j][k] = min(dp[1][j][k], dp[0][j][k] + tasks[i - 1].timeB);
                } else if (tasks[i - 1].type == 2) {
                    dp[0][j][k] = min(dp[0][j][k], dp[1][j][k] + tasks[i - 1].timeA);
                    dp[1][j][k] = min(dp[1][j][k], dp[1][j][k]);
                } else {
                    dp[0][j][k] = min(dp[0][j][k], dp[0][j][k] + tasks[i - 1].timeA);
                    dp[1][j][k] = min(dp[1][j][k], dp[1][j][k] + tasks[i - 1].timeB);
                }
            }
        }
    }
    
    int result = min(dp[0][n][0], dp[1][n][0]);
    printf("%d\n", result);
    
    return 0;
}