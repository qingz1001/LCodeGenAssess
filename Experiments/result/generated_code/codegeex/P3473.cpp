#include <stdio.h>
#include <string.h>

#define MAXN 101

int n, m, k, x, y;
char grid[MAXN][MAXN];
long long dp[MAXN][MAXN][2];
int visited[MAXN][MAXN][2];

long long dfs(int row, int col, int direction) {
    if (row == n || col > m || grid[row][col] == '*') {
        return 0;
    }
    if (visited[row][col][direction]) {
        return dp[row][col][direction];
    }
    visited[row][col][direction] = 1;
    long long result = 0;
    if (direction == 0) { // moving north
        result = dfs(row - 1, col, 0) + dfs(row, col + 1, 1);
    } else { // moving east
        result = dfs(row, col + 1, 1) + dfs(row - 1, col, 0);
    }
    return dp[row][col][direction] = result % k;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    scanf("%d %d", &x, &y);
    for (int i = 1; i <= n; i++) {
        scanf("%s", grid[i] + 1);
    }
    memset(visited, 0, sizeof(visited));
    long long result = dfs(n, 1, 0);
    printf("%lld\n", result);
    return 0;
}