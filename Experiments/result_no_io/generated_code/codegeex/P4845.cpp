#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1001

int n, k, r;
int w[MAXN];
int head[MAXN], to[MAXN * 2], next[MAXN * 2], tot;

void add(int x, int y) {
    to[tot] = y;
    next[tot] = head[x];
    head[x] = tot++;
}

int dp[MAXN][MAXN][2]; // dp[u][j][0/1] 表示在 u 的子树中放置 j 个摄像头，u 本身放不放

void dfs(int u, int fa) {
    dp[u][0][0] = 0;
    dp[u][1][1] = w[u];
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        for (int j = k; j >= 0; j--) {
            for (int x = j; x >= 0; x--) {
                dp[u][j][0] = fmax(dp[u][j][0], dp[u][x][0] + dp[v][j - x][0]);
                dp[u][j][1] = fmax(dp[u][j][1], dp[u][x][1] + dp[v][j - x][0], dp[u][x][0] + dp[v][j - x][1]);
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(head, -1, sizeof(head));
        tot = 0;
        scanf("%d%d%d", &n, &k, &r);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &w[i]);
        }
        for (int i = 1; i < n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            add(x, y);
            add(y, x);
        }
        dfs(1, 0);
        int ans = 0;
        for (int i = 0; i <= k; i++) {
            ans = fmax(ans, dp[1][i][0]);
            ans = fmax(ans, dp[1][i][1]);
        }
        printf("%d\n", ans);
    }
    return 0;
}