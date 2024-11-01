#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

int n, m, u[MAXM], v[MAXM], ans, deg[MAXN];
int *head[MAXN], *tail[MAXN], *cnt[MAXN];
int *h[MAXN], *t[MAXN], *c[MAXN], *p;

void add(int *h, int *t, int *c, int *p, int x, int y) {
    *t = *p;
    *(++p) = x;
    *(++p) = y;
    *(++t) = 0;
}

int main() {
    scanf("%d%d", &n, &m);
    p = h[0] = (int*)malloc(2 * n * sizeof(int));
    t[0] = -1;
    for (int i = 1; i < n; i++) {
        h[i] = p;
        t[i] = t[i - 1];
        c[i] = c[i - 1] + 1;
        p += c[i];
    }
    for (int i = 1; i < n; i++) {
        add(h, t, c, p, 0, i);
        add(h, t, c, p, i, 0);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", u + i, v + i);
        add(h, t, c, p, u[i], v[i]);
        add(h, t, c, p, v[i], u[i]);
    }
    for (int i = 1; i < n; i++) {
        p = h[i];
        for (int j = 1; j <= c[i]; j += 2) {
            int x = p[0], y = p[1];
            p += 2;
            for (int k = 1; k <= c[x]; k += 2) {
                if (y == p[0]) {
                    deg[i]++;
                    break;
                }
                p += 2;
            }
        }
    }
    for (int i = 1; i < n; i++) {
        p = h[i];
        for (int j = 1; j <= c[i]; j += 2) {
            int x = p[0], y = p[1];
            p += 2;
            for (int k = 1; k <= c[x]; k += 2) {
                if (y == p[0]) {
                    ans += deg[i] - deg[x];
                    break;
                }
                p += 2;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}