#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

int n, m, x, y, tot, head[MAXN], to[MAXM], nxt[MAXM], c[MAXM], d[MAXM], que[MAXN], l, r, ans;

void add(int u, int v, int w) {
    to[++tot] = v;
    nxt[tot] = head[u];
    c[tot] = w;
    head[u] = tot;
}

void bfs() {
    while (l <= r) {
        x = que[l++];
        for (int i = head[x]; i; i = nxt[i]) {
            y = to[i];
            if (d[y] == -1) {
                d[y] = d[x] + c[i];
                if (d[y] > ans) {
                    ans = d[y];
                    if (ans == m) return;
                }
                que[++r] = y;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    memset(d, -1, sizeof(d));
    d[1] = 0;
    que[r = 1] = 1;
    while (n--) {
        scanf("%d%d", &x, &y);
        if (x == 0 && y == 0) {
            bfs();
            memset(d, -1, sizeof(d));
            d[1] = 0;
            que[r = 1] = 1;
        } else {
            add(x, y, 1);
            add(y, x, 1);
        }
    }
    bfs();
    printf("%d\n", ans);
    return 0;
}