#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001
#define MAXM 5001

int n, m;
int f[MAXN], ne[MAXM], e[MAXM], v[MAXM], h[MAXN], p[MAXN];
double g[MAXN][MAXN], dp[MAXN][MAXN];

void init() {
    memset(h, -1, sizeof(h));
    memset(g, 0, sizeof(g));
}

void add(int x, int y, int z) {
    ne[m] = h[x];
    e[m] = y;
    v[m] = z;
    h[x] = m++;
}

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (g[i][j] < g[i][k] + g[k][j]) {
                    g[i][j] = g[i][k] + g[k][j];
                }
            }
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = -1e9;
        }
    }
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (g[i][j] == g[i][k] + g[k][j]) {
                    dp[i][j] = fmax(dp[i][j], dp[i][k] + dp[k][j] + f[j] - g[i][j]);
                }
            }
        }
    }
    double ans = -1e9;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (g[i][j] > 0) {
                ans = fmax(ans, dp[i][j] / g[i][j]);
            }
        }
    }
    printf("%.2lf\n", ans);
}

int main() {
    scanf("%d%d", &n, &m);
    init();
    for (int i = 1; i <= n; i++) {
        scanf("%d", &f[i]);
    }
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        g[x][y] = z;
    }
    floyd();
    solve();
    return 0;
}