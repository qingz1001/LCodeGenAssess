#include <stdio.h>
#include <string.h>

#define MAX_N 200
#define MAX_M 200

int n, m, k;
int score[MAX_N][MAX_M];
int bullet[MAX_N][MAX_M];
int dp[MAX_N * MAX_M + 1][MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            char c;
            scanf("%d %c", &score[i][j], &c);
            bullet[i][j] = (c == 'Y');
        }
    }

    memset(dp, -1, sizeof(dp));
    dp[k][0] = 0;

    for (int i = 0; i < n * m; i++) {
        for (int b = 0; b <= k + i; b++) {
            for (int j = 0; j < m; j++) {
                if (dp[b][j] == -1) continue;
                
                int row = i / m;
                int col = i % m;
                
                if (b > 0) {
                    int new_b = b - 1 + bullet[row][col];
                    int new_score = dp[b][j] + score[row][col];
                    dp[new_b][col] = max(dp[new_b][col], new_score);
                }
                
                if (j != col) {
                    dp[b][col] = max(dp[b][col], dp[b][j]);
                }
            }
        }
    }

    int result = 0;
    for (int b = 0; b <= k + n * m; b++) {
        for (int j = 0; j < m; j++) {
            result = max(result, dp[b][j]);
        }
    }

    printf("%d\n", result);

    return 0;
}