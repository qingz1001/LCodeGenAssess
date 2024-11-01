#include <stdio.h>
#include <stdlib.h>

#define MAXN 101

int n, m;
int w[MAXN], c[MAXN];
int head[MAXN], next[MAXN * 2], to[MAXN * 2], tot;

void add(int u, int v) {
    next[++tot] = head[u];
    head[u] = tot;
    to[tot] = v;
}

double dp[MAXN][MAXN][2];

void dfs(int u, int fa) {
    for (int i = head[u]; i; i = next[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
    }
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m - i; j++) {
            dp[u][i][0] = dp[u][i][1] = 0;
            for (int k = head[u]; k; k = next[k]) {
                int v = to[k];
                if (v == fa) continue;
                double max1 = -1, max2 = -1;
                for (int x = 0; x <= i; x++) {
                    for (int y = 0; y <= j; y++) {
                        if (dp[u][x][0] * dp[v][y][1] > max1) {
                            max1 = dp[u][x][0] * dp[v][y][1];
                            max2 = dp[u][x][0] * dp[v][y][0];
                        }
                    }
                }
                dp[u][i][0] += max1;
                dp[u][i][1] += max2;
            }
            dp[u][i][0] += w[u];
            dp[u][i][1] += c[u];
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    double ans = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m - i; j++) {
            if (dp[1][i][1] && dp[1][i][0] / dp[1][i][1] > ans) {
                ans = dp[1][i][0] / dp[1][i][1];
            }
        }
    }
    printf("%.1f\n", ans);
    return 0;
}