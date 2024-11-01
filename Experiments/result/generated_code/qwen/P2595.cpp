#include <stdio.h>
#include <stdlib.h>

#define MOD 19901013

int n, m;
char grid[16][16];
int dp[16][1 << 16];

void dfs(int row, int col, int state) {
    if (row == n) {
        dp[n][state] = (dp[n][state] + 1) % MOD;
        return;
    }
    if (col == m) {
        dfs(row + 1, 0, 0);
        return;
    }
    if (grid[row][col] == 'x') {
        dfs(row, col + 1, state);
        return;
    }

    dfs(row, col + 1, state); // Skip this cell
    if (col + 1 < m && grid[row][col + 1] != 'x') {
        dfs(row, col + 2, state | (1 << (row * m + col)));
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    dfs(0, 0, 0);

    int result = 0;
    for (int i = 0; i < (1 << (n * m)); i++) {
        if ((i & (i >> 1)) == 0) { // Check no two adjacent cells are occupied
            result = (result + dp[n][i]) % MOD;
        }
    }

    printf("%d\n", result);

    return 0;
}