#include <stdio.h>
#include <string.h>

#define N 200005

int n, m;
double p[N], q[N], ans, f[N][2], g[N][2];
char s[10];

int main() {
    scanf("%d%d%s", &n, &m, s);
    scanf("%lf", &p[1]);
    for (int i = 2; i <= n; i++) {
        scanf("%lf%lf", &p[i], &q[i]);
    }

    while (m--) {
        scanf("%s", s);
        if (s[0] == 'a') {
            int x, c;
            scanf("%d%d", &x, &c);
            if (c) {
                ans += f[x - 1][0] * (1 - p[x]) + (1 - f[x - 1][0]) * q[x];
                f[x][0] = f[x - 1][0] * (1 - p[x]) / (1 - f[x - 1][1] * q[x]);
                f[x][1] = 1 - f[x][0];
                g[x][0] = g[x - 1][0] + (1 - f[x - 1][0]) * q[x];
                g[x][1] = g[x - 1][1] + f[x - 1][0] * (1 - p[x]);
            } else {
                ans += f[x - 1][1] * p[x] + (1 - f[x - 1][1]) * (1 - q[x]);
                f[x][0] = f[x - 1][0] + (1 - f[x - 1][1]) * (1 - q[x]);
                f[x][1] = f[x - 1][1] + f[x - 1][0] * p[x];
                g[x][0] = g[x - 1][0] * (1 - q[x]) / (1 - f[x - 1][1] * p[x]);
                g[x][1] = 1 - g[x][0];
            }
        } else {
            int x;
            scanf("%d", &x);
            ans -= f[x][0] * (1 - p[x]) + (1 - f[x][0]) * q[x];
            f[x][0] = g[x - 1][0] * (1 - p[x]) / (1 - g[x - 1][1] * q[x]);
            f[x][1] = 1 - f[x][0];
            g[x][0] = g[x - 1][0] + (1 - g[x - 1][1]) * q[x];
            g[x][1] = g[x - 1][1] + g[x - 1][0] * (1 - p[x]);
        }
        printf("%.6lf\n", ans);
    }
    return 0;
}