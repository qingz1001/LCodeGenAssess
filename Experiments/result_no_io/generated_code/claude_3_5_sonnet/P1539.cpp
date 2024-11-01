#include <stdio.h>
#include <string.h>

#define MAX_N 15
#define MAX_M 15
#define MOD 10007

char matrix[MAX_N][MAX_M];
int n, m;
int dp[MAX_N][MAX_M][1 << MAX_M];

int dfs(int row, int col, int prev_row) {
    if (col == m) {
        return dfs(row + 1, 0, prev_row);
    }
    if (row == n) {
        return 1;
    }
    
    if (dp[row][col][prev_row] != -1) {
        return dp[row][col][prev_row];
    }
    
    int result = 0;
    int up = (prev_row >> col) & 1;
    int left = (col > 0) ? ((prev_row >> (col - 1)) & 1) : 0;
    
    for (int current = 0; current <= 1; current++) {
        if (matrix[row][col] != '.' && matrix[row][col] - '0' != current) {
            continue;
        }
        
        if ((current == 1 && up == 1) || (current == 1 && left == 1)) {
            continue;
        }
        
        int new_prev_row = (prev_row & ~(1 << col)) | (current << col);
        result = (result + dfs(row, col + 1, new_prev_row)) % MOD;
    }
    
    return dp[row][col][prev_row] = result;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }
    
    memset(dp, -1, sizeof(dp));
    
    int ans = dfs(0, 0, 0);
    printf("%d\n", ans);
    
    return 0;
}