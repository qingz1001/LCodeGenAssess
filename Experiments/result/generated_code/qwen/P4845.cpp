#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 0x3f3f3f3f

int n, k, r;
int w[MAXN];
int tree[MAXN][MAXN];
int dp[MAXN][MAXN];

void dfs(int u, int fa) {
    for (int i = 1; i <= n; i++) {
        if (tree[u][i] && i != fa) {
            dfs(i, u);
            dp[u][0] += dp[i][0];
            dp[u][1] += dp[i][1];
            dp[u][1] = fmax(dp[u][1], dp[i][0] + w[i]);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &k, &r);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &w[i]);
            for (int j = 1; j <= n; j++) {
                tree[i][j] = 0;
            }
        }
        for (int i = 1; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            tree[x][y] = 1;
            tree[y][x] = 1;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = -INF;
            }
        }
        dp[1][0] = 0;
        dp[1][1] = w[1];
        dfs(1, 0);

        printf("%d\n", dp[1][k]);
    }
    return 0;
}