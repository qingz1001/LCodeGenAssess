#include <stdio.h>
#include <string.h>

#define N 16
#define MAXCOLOR 20

int n;
int x[N], y[N], a[N], b[N], c[N], f[1 << N][MAXCOLOR], pre[1 << N][MAXCOLOR], g[1 << N][MAXCOLOR];

void solve() {
    int i, j, k, t, mask, min;
    for (i = 1; i < (1 << n); i++) {
        for (j = 1; j <= 20; j++) {
            min = 0x7fffffff;
            for (k = 0; k < n; k++) {
                if (i & (1 << k)) {
                    mask = (1 << k);
                    if (y[k] == 0 || (i & mask) == mask) {
                        t = f[i - mask][c[k]];
                        if (t < min) {
                            min = t;
                            pre[i][j] = k;
                        }
                    }
                }
            }
            f[i][j] = min + 1;
        }
    }
    mask = (1 << n) - 1;
    min = 0x7fffffff;
    for (i = 1; i <= 20; i++) {
        if (f[mask][i] < min) {
            min = f[mask][i];
            g[mask][i] = 1;
        }
    }
    while (mask) {
        i = pre[mask][i];
        j = c[i];
        mask ^= (1 << i);
        g[mask][j] = 1;
    }
}

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d%d%d%d%d", &y[i], &x[i], &b[i], &a[i], &c[i]);
        a[i] -= x[i];
        b[i] -= y[i];
    }
    solve();
    for (i = 1; i <= 20; i++) {
        if (g[0][i]) {
            printf("%d\n", g[0][i]);
            break;
        }
    }
    return 0;
}