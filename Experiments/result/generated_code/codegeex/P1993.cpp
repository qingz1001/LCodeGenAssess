#include <stdio.h>
#include <stdlib.h>

#define MAXN 5000
#define MAXM 5000

int n, m;
int head[MAXN + 1], to[MAXM * 2 + 1], nxt[MAXM * 2 + 1], val[MAXM * 2 + 1], cnt;

void add(int u, int v, int w) {
    to[++cnt] = v;
    val[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

int dis[MAXN + 1], vis[MAXN + 1];

int spfa() {
    for (int i = 1; i <= n; i++) {
        dis[i] = 1e9;
        vis[i] = 0;
    }
    dis[0] = 0;
    vis[0] = 1;
    while (1) {
        int u = 0;
        for (int i = 1; i <= n; i++) {
            if (!vis[i] && (u == 0 || dis[i] < dis[u])) {
                u = i;
            }
        }
        if (u == 0) break;
        vis[u] = 1;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i], w = val[i];
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
            }
        }
    }
    return dis[n];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int op, a, b, c;
        scanf("%d", &op);
        if (op == 3) {
            scanf("%d%d", &a, &b);
            add(a, b, 0);
            add(b, a, 0);
        } else {
            scanf("%d%d%d", &a, &b, &c);
            if (op == 1) {
                add(a, b, c);
            } else {
                add(b, a, -c);
            }
        }
    }
    int d = spfa();
    if (d == 1e9) {
        printf("No\n");
    } else {
        printf("Yes\n");
    }
    return 0;
}