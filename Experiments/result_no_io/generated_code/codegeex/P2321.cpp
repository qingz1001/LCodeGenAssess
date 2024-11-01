#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000
#define MAXQ 1000000

int n, m, q;
int a[MAXN+5], b[MAXN+5], c[MAXN+5], d[MAXN+5];
int f[MAXN+5][MAXN+5];
int g[MAXQ+5];

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &d[i]);

    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j] = g[q - b[i] * j];
            for (int k = 1; k <= j; k++) {
                f[i][j] = (f[i][j] > f[i][j-k] + g[q - a[i] * (j-k) - c[i]]) ? f[i][j] : f[i][j-k] + g[q - a[i] * (j-k) - c[i]];
            }
            g[q - b[i] * j] = (g[q - b[i] * j] > f[i][j] + d[i]) ? g[q - b[i] * j] : f[i][j] + d[i];
        }
    }

    int max = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            max = (max > f[i][j]) ? max : f[i][j];
        }
    }

    printf("%d\n", max);

    return 0;
}