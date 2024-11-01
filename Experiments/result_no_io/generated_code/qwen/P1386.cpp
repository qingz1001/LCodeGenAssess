#include <stdio.h>
#include <stdlib.h>

#define MAXN 305
#define MOD 1000000007

int T, n, m, M;
int a[MAXN], fixed[MAXN];
int dp[MAXN][MAXN];

void init() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = -1;
        }
    }
}

int dfs(int pos, int used) {
    if (pos == n + 1) return 1;
    if (dp[pos][used] != -1) return dp[pos][used];

    int res = 0;
    if (fixed[pos]) {
        if (used & (1 << (a[pos] - 1))) return 0;
        res = dfs(pos + 1, used | (1 << (a[pos] - 1)));
    } else {
        for (int i = 1; i <= n; ++i) {
            if (!(used & (1 << (i - 1)))) {
                res = (res + dfs(pos + 1, used | (1 << (i - 1)))) % MOD;
            }
        }
    }

    return dp[pos][used] = res;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &m, &M);
        init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < m; ++i) {
            int p, q;
            scanf("%d %d", &p, &q);
            fixed[p] = 1;
            a[p] = q;
        }

        int result = dfs(1, 0);
        if (result > 0) {
            printf("YES %d\n", result);
        } else {
            printf("NO\n");
        }
    }
    return 0;
}