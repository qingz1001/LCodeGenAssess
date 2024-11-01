#include <stdio.h>
#include <stdbool.h>

#define MAXN 100
#define MAXM 100

int n, m, k, x, y;
bool visited[MAXN][MAXM];
int dp[MAXN][MAXM][4]; // 0: north, 1: east, 2: south, 3: west

int mod(int a, int b) {
    return (a % b + b) % b;
}

int dfs(int i, int j, int dir) {
    if (i == x - 1 && j == y - 1) return 1;
    if (i < 0 || i >= n || j < 0 || j >= m || visited[i][j]) return 0;
    if (dp[i][j][dir] != -1) return dp[i][j][dir];

    visited[i][j] = true;
    int res = 0;

    if (dir == 0) { // north
        res = (res + dfs(i, j + 1, 1)) % k; // turn right to east
        res = (res + dfs(i - 1, j, 0)) % k; // continue north
    } else if (dir == 1) { // east
        res = (res + dfs(i + 1, j, 2)) % k; // turn right to south
        res = (res + dfs(i, j + 1, 1)) % k; // continue east
    } else if (dir == 2) { // south
        res = (res + dfs(i, j - 1, 3)) % k; // turn right to west
        res = (res + dfs(i + 1, j, 2)) % k; // continue south
    } else if (dir == 3) { // west
        res = (res + dfs(i - 1, j, 0)) % k; // turn right to north
        res = (res + dfs(i, j - 1, 3)) % k; // continue west
    }

    visited[i][j] = false;
    dp[i][j][dir] = res;
    return res;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    scanf("%d %d", &x, &y);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int d = 0; d < 4; d++) {
                dp[i][j][d] = -1;
            }
        }
    }

    int result = dfs(n - 1, 0, 0);
    printf("%d\n", result);

    return 0;
}