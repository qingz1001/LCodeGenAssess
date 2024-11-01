#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 205
#define MAXM 400005
#define INF 1000000000

int n, m, k, q;
int u[MAXN];
int v[MAXM], w[MAXM], r[MAXM];
double g[MAXN][MAXN];

void floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][j] > g[i][k] + g[k][j]) {
                    g[i][j] = g[i][k] + g[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &k, &q);
    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        u[a] = b;
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &v[i], &w[i], &r[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) g[i][j] = 0;
            else g[i][j] = INF;
        }
    }
    for (int i = 0; i < m; i++) {
        g[v[i]][w[i]] = (double)r[i];
        g[w[i]][v[i]] = (double)r[i];
    }
    for (int i = 1; i <= n; i++) {
        if (u[i] != 0) {
            for (int j = 0; j < n; j++) {
                g[0][j] = (double)u[i];
                g[j][0] = (double)u[i];
            }
        }
    }
    floyd();
    while (q--) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a > b) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        double ans = g[a][b];
        printf("%.2lf\n", ans);
    }
    return 0;
}