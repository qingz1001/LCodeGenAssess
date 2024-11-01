#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 1005

int n, m;
int a[MAXN], b[MAXM], w[MAXN][MAXM];
int f[MAXM], g[MAXM];

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &w[i][j]);

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) f[j] = g[j] = 0;
        for (int j = 1; j <= m; j++)
            for (int k = b[j]; k >= a[i]; k--)
                f[k] = f[k] > f[k - a[i]] + w[i][j] ? f[k] : f[k - a[i]] + w[i][j];
        for (int j = 1; j <= m; j++)
            for (int k = b[j]; k >= a[i]; k--)
                g[k] = g[k] > g[k - a[i]] + w[i][j] ? g[k] : g[k - a[i]] + w[i][j];
        for (int j = 0; j <= m; j++) f[j] += g[j];
        int maxn = 0, maxp = 0;
        for (int j = 0; j <= m; j++)
            if (f[j] > maxn) {
                maxn = f[j];
                maxp = j;
            }
        for (int j = 0; j <= m; j++) f[j] = g[j] = 0;
        for (int j = 1; j <= m; j++)
            for (int k = b[j]; k >= a[i]; k--)
                f[k] = f[k] > f[k - a[i]] + w[i][j] ? f[k] : f[k - a[i]] + w[i][j];
        for (int j = 0; j <= m; j++) f[j] += g[j];
        for (int j = m; j >= 0; j--)
            if (f[j] == maxn) {
                maxp = j;
                break;
            }
        printf("%d\n", maxp);
    }
}

int main() {
    for (int i = 1; i <= 10; i++) {
        char input[20], output[20];
        sprintf(input, "drawer%d.in", i);
        sprintf(output, "drawer%d.out", i);
        freopen(input, "r", stdin);
        freopen(output, "w", stdout);
        solve();
        fclose(stdin);
        fclose(stdout);
    }
    return 0;
}