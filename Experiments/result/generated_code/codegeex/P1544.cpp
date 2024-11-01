#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

long long pyramid[MAX_N + 1][MAX_N + 1];
int n, k;

// Function to read input
void read_input() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            scanf("%lld", &pyramid[i][j]);
        }
    }
}

// Function to calculate maximum score
long long calculate_max_score() {
    long long dp[MAX_N + 1][MAX_N + 1][MAX_N + 1];
    
    // Initialize the dp array
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int l = 0; l <= k; l++) {
                dp[i][j][l] = -1;
            }
        }
    }
    
    // Base case
    dp[1][1][0] = pyramid[1][1];
    
    // Fill dp array
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int l = 0; l <= k; l++) {
                if (l > 0) {
                    dp[i][j][l] = dp[i - 1][j][l - 1] + pyramid[i][j] * 3;
                }
                dp[i][j][l] = dp[i][j][l] > dp[i - 1][j - 1][l] + pyramid[i][j] ? dp[i][j][l] : dp[i - 1][j - 1][l] + pyramid[i][j];
                dp[i][j][l] = dp[i][j][l] > dp[i - 1][j][l] ? dp[i][j][l] : dp[i - 1][j][l];
            }
        }
    }
    
    // Find the maximum score
    long long max_score = 0;
    for (int l = 0; l <= k; l++) {
        max_score = max_score > dp[n][n][l] ? max_score : dp[n][n][l];
    }
    
    return max_score;
}

int main() {
    read_input();
    long long max_score = calculate_max_score();
    printf("%lld\n", max_score);
    return 0;
}