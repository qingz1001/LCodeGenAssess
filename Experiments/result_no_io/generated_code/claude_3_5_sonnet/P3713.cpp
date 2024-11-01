#include <stdio.h>
#include <string.h>

#define MOD 1000000009
#define MAXN 31

char map[MAXN][MAXN];
int m, n;
long long dp[MAXN][MAXN][MAXN][MAXN];

long long dfs(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    if (dp[x1][y1][x2][y2] != -1) return dp[x1][y1][x2][y2];
    
    long long res = 0;
    if (x1 == x2 && y1 == y2) return 0;
    if ((x1 == x2 && y2 - y1 == 1) || (y1 == y2 && x2 - x1 == 1)) return 1;
    
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            if (i == x1 && j == y1) continue;
            if (i == x2 && j == y2) continue;
            
            long long left = dfs(x1, y1, i, j);
            long long right = dfs(i, j, x2, y2);
            res = (res + left * right) % MOD;
        }
    }
    
    dp[x1][y1][x2][y2] = res;
    return res;
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        scanf("%s", map[i]);
    }
    
    memset(dp, -1, sizeof(dp));
    
    long long ans = 0;
    for (int x1 = 0; x1 < m; x1++) {
        for (int y1 = 0; y1 < n; y1++) {
            for (int x2 = x1; x2 < m; x2++) {
                for (int y2 = y1; y2 < n; y2++) {
                    if (x1 == x2 && y1 == y2) continue;
                    long long paths = dfs(x1, y1, x2, y2);
                    ans = (ans + paths * paths) % MOD;
                }
            }
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}