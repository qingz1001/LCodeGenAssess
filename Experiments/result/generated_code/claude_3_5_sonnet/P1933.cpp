#include <stdio.h>
#include <string.h>

#define MOD 11192869
#define MAXN 3
#define MAXM 50

int n, m;
int T[MAXN][MAXM];
int L[MAXN * MAXM];
int dp[MAXN][MAXM][1 << MAXN][2];

int dfs(int x, int y, int mask, int last) {
    if (y == m) return mask == (1 << n) - 1;
    if (dp[x][y][mask][last] != -1) return dp[x][y][mask][last];

    int res = 0;
    for (int i = 0; i < n; i++) {
        if (!(mask & (1 << i)) && T[i][y] == L[x * m + y]) {
            if (last == 0 || (x == 0 && i == n - 1) || (x == n - 1 && i == 0) || abs(x - i) == 1) {
                res = (res + dfs(i, y + 1, mask | (1 << i), 1)) % MOD;
            }
        }
    }

    return dp[x][y][mask][last] = res;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &T[i][j]);
        }
    }
    
    for (int i = 0; i < n * m; i++) {
        scanf("%d", &L[i]);
    }

    memset(dp, -1, sizeof(dp));

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (T[i][0] == L[0]) {
            ans = (ans + dfs(i, 1, 1 << i, 1)) % MOD;
        }
    }

    printf("%d\n", ans);
    return 0;
}