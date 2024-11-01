#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 1000005

int n, m, a[MAXN], ans;
int color[MAXM], next[MAXM], prev[MAXM], head[MAXM];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (i == 1) {
            color[i] = a[i];
            next[i] = i + 1;
            prev[i] = 0;
            head[a[i]] = i;
        } else {
            if (a[i] != a[i - 1]) {
                ans++;
            }
            color[i] = a[i];
            next[i] = i + 1;
            prev[i] = i - 1;
            if (head[a[i]] == 0) {
                head[a[i]] = i;
            }
            if (i < n) {
                prev[i + 1] = i;
                next[i + 1] = next[i];
                next[i] = i + 1;
            }
        }
    }
    while (m--) {
        int op, x, y;
        scanf("%d", &op);
        if (op == 2) {
            printf("%d\n", ans);
        } else {
            scanf("%d %d", &x, &y);
            if (x == y) {
                continue;
            }
            int hx = head[x], hy = head[y];
            int p = hx;
            while (p) {
                int c = color[p];
                if (c == x) {
                    color[p] = y;
                    if (prev[p] == 0) {
                        head[y] = p;
                    }
                    if (next[p] == 0) {
                        head[x] = 0;
                    }
                    if (prev[p] != 0) {
                        next[prev[p]] = next[p];
                    }
                    if (next[p] != 0) {
                        prev[next[p]] = prev[p];
                    }
                    if (prev[p] == 0 && next[p] == 0) {
                        head[x] = 0;
                    }
                    if (prev[p] == 0) {
                        head[y] = p;
                    }
                    if (next[p] == 0) {
                        head[x] = 0;
                    }
                }
                p = next[p];
            }
            if (head[x] == 0) {
                ans -= (prev[hx] == 0) + (next[hx] == 0);
            }
            if (head[y] != 0) {
                ans += (prev[hy] == 0) + (next[hy] == 0);
            }
        }
    }
    return 0;
}