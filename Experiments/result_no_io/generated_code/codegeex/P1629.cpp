#include <stdio.h>
#include <string.h>

#define MAXN 1001
#define MAXM 100001
#define INF 0x3f3f3f3f

int n, m;
int u[MAXM], v[MAXM], w[MAXM];
int d[MAXN][MAXN], f[MAXN][MAXN], g[MAXN][MAXN];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
        d[u[i]][v[i]] = w[i];
    }

    // 初始化距离矩阵
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                f[i][j] = g[i][j] = 0;
            } else {
                f[i][j] = g[i][j] = INF;
            }
        }
    }

    // 计算所有节点对之间的最短路径
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = f[j][i] = (f[i][j] < f[i][k] + d[k][j] + f[k][j]) ? f[i][j] : f[i][k] + d[k][j] + f[k][j];
                g[i][j] = g[j][i] = (g[i][j] < g[i][k] + d[k][j] + g[k][j]) ? g[i][j] : g[i][k] + d[k][j] + g[k][j];
            }
        }
    }

    int ans = INF;
    for (int i = 2; i <= n; i++) {
        ans = (ans < f[1][i] + g[i][1]) ? ans : f[1][i] + g[i][1];
    }

    printf("%d\n", ans);
    return 0;
}