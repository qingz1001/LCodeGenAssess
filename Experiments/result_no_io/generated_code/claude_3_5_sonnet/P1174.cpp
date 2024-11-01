#include <stdio.h>
#include <string.h>

#define MAX_N 201
#define MAX_M 201
#define MAX_K 201

int n, m, k;
int score[MAX_N][MAX_M];
int bonus[MAX_N][MAX_M];
int dp[MAX_K][MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            char c;
            scanf("%d %c", &score[i][j], &c);
            bonus[i][j] = (c == 'Y');
        }
    }
    
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    
    int max_score = 0;
    
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < m; j++) {
            if (dp[i][j] == -1) continue;
            
            max_score = max(max_score, dp[i][j]);
            
            if (i == k) continue;
            
            for (int col = 0; col < m; col++) {
                int row = 0;
                while (row < n && score[row][col] == 0) row++;
                
                if (row == n) continue;
                
                int new_bullets = i + 1 + bonus[row][col];
                if (new_bullets > k) new_bullets = k;
                
                dp[new_bullets][col] = max(dp[new_bullets][col], dp[i][j] + score[row][col]);
            }
        }
    }
    
    printf("%d\n", max_score);
    
    return 0;
}