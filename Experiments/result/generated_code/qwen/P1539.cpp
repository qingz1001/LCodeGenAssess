#include <stdio.h>
#define MOD 10007

int n, m;
char grid[226][226];
int dp[226][226][2];

void dfs(int x, int y, int last) {
    if (x == n) {
        for (int i = 0; i < m; i++) {
            dp[n][i][grid[n-1][i]-'0']++;
        }
        return;
    }
    if (y == m) {
        dfs(x + 1, 0, -1);
        return;
    }
    if (grid[x][y] != '.') {
        dfs(x, y + 1, grid[x][y] - '0');
        return;
    }
    int sum = 0;
    if (last != -1) {
        sum = (sum + dp[x][y+1][1 ^ last]) % MOD;
    } else {
        sum = (sum + dp[x][y+1][0]) % MOD;
        sum = (sum + dp[x][y+1][1]) % MOD;
    }
    dfs(x, y + 1, 0);
    dfs(x, y + 1, 1);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }
    dfs(0, 0, -1);
    printf("%d\n", dp[n][m-1][0] + dp[n][m-1][1]);
    return 0;
}