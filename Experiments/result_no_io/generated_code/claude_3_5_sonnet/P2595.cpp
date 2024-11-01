#include <stdio.h>
#include <string.h>

#define MOD 19901013
#define MAXN 15
#define MAXM 15

int n, m;
char grid[MAXN][MAXM];
int dp[MAXN][MAXM][1 << MAXM];

int solve(int row, int col, int mask) {
    if (col == m) {
        return solve(row + 1, 0, mask);
    }
    if (row == n) {
        for (int i = 0; i < m - 1; i++) {
            if (((mask >> i) & 3) == 0) {
                return 0;
            }
        }
        return 1;
    }
    
    if (dp[row][col][mask] != -1) {
        return dp[row][col][mask];
    }
    
    int result = 0;
    
    // 不放骨牌
    result = (result + solve(row, col + 1, mask & ~(1 << col))) % MOD;
    
    // 放横向骨牌
    if (col < m - 1 && grid[row][col] == '.' && grid[row][col + 1] == '.' && ((mask & (1 << col)) == 0) && ((mask & (1 << (col + 1))) == 0)) {
        result = (result + solve(row, col + 2, mask | (1 << col) | (1 << (col + 1)))) % MOD;
    }
    
    // 放纵向骨牌
    if (row < n - 1 && grid[row][col] == '.' && grid[row + 1][col] == '.' && ((mask & (1 << col)) == 0)) {
        result = (result + solve(row, col + 1, mask | (1 << col))) % MOD;
    }
    
    dp[row][col][mask] = result;
    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    
    memset(dp, -1, sizeof(dp));
    int result = solve(0, 0, 0);
    printf("%d\n", result);
    
    return 0;
}