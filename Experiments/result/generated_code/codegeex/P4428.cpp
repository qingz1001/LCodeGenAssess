#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m, a[MAXN], b[MAXN], c[MAXN], d[MAXN], e[MAXN];
long long s[MAXN], ans[MAXN];

int main() {
    int i, j, l, r, t, x, y, z, p;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = b[i - 1] + a[i];
        c[i] = c[i - 1] + a[i] * a[i];
        d[i] = d[i - 1] + a[i] * a[i] * a[i];
        e[i] = e[i - 1] + a[i] * a[i] * a[i] * a[i];
    }
    scanf("%d", &m);
    for (i = 1; i <= m; i++) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d", &x);
            a[x] ^= 1;
            b[x] = b[x - 1] + a[x];
            c[x] = c[x - 1] + a[x] * a[x];
            d[x] = d[x - 1] + a[x] * a[x] * a[x];
            e[x] = e[x - 1] + a[x] * a[x] * a[x] * a[x];
        } else {
            scanf("%d%d", &l, &r);
            s[i] = (b[r] - b[l - 1]) * (r - l + 1) - (c[r] - c[l - 1]) / 2 + (d[r] - d[l - 1]) / 3 - (e[r] - e[l - 1]) / 4;
            ans[i] = s[i] + s[i - 1];
        }
    }
    for (i = 1; i <= m; i++) {
        if (ans[i] > 0) {
            printf("%lld\n", ans[i]);
        }
    }
    return 0;
}