#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 1000000

int T;
int n, k, r;
int w[MAXN];
int tree[MAXN][MAXN];
int dp[MAXN][MAXN];

void dfs(int u, int p, int depth) {
    for (int v = 1; v <= n; v++) {
        if (tree[u][v] && v != p) {
            dfs(v, u, depth + 1);
            dp[u][depth] += dp[v][depth - 1];
        }
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &k, &r);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &w[i]);
        }
        for (int i = 1; i <= n; i++) {
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
            for (int j = 0; j <= r; j++) {
                dp[i][j] = 0;
            }
        }

        for (int i = 1; i <= n; i++) {
            dfs(i, -1, 0);
        }

        int result = 0;
        for (int i = 1; i <= n; i++) {
            int sum = 0;
            for (int j = 0; j <= r; j++) {
                sum += dp[i][j];
            }
            result = fmax(result, sum);
        }

        printf("%d\n", result);
    }
    return 0;
}