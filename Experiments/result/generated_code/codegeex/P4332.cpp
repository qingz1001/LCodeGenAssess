#include <stdio.h>
#include <stdlib.h>

#define MAXN 1500005

int n, q, x[MAXN], y[MAXN], z[MAXN], val[MAXN], fa[MAXN], son[MAXN][3], tag[MAXN], res[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &x[i], &y[i], &z[i]);
        fa[x[i]] = y[i];
        fa[y[i]] = z[i];
        fa[z[i]] = -1;
    }
    for (int i = n + 1; i <= 3 * n + 1; i++) fa[i] = -2;
    for (int i = 1; i <= 3 * n + 1; i++) scanf("%d", &val[i]);

    for (int i = n; i >= 1; i--) {
        if (val[x[i]] + val[y[i]] + val[z[i]] >= 2) val[i] = 1;
        else val[i] = 0;
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int pos;
        scanf("%d", &pos);
        int p = pos;
        while (p != -1) {
            if (fa[p] == -2) {
                if (val[p] == 0) {
                    val[p] = 1;
                    res[i] = 1;
                }
                break;
            }
            if (tag[p] == 0) {
                if (val[x[p]] + val[y[p]] + val[z[p]] >= 2) val[p] = 1;
                else val[p] = 0;
                if (val[p] != val[fa[p]]) {
                    tag[fa[p]] = 1;
                }
            }
            p = fa[p];
        }
        tag[1] = 0;
    }

    for (int i = 1; i <= q; i++) {
        printf("%d\n", res[i]);
    }

    return 0;
}