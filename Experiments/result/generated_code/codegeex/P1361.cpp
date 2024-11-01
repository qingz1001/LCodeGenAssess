#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define INF 0x3f3f3f3f

int n, m;
int a[MAXN], b[MAXN];
int k[MAXN], c1[MAXN], c2[MAXN], w[MAXN];
int u[MAXN], v[MAXN], flow[MAXN], dis[MAXN], pre[MAXN];
int s, t;
int ans;

int min(int a, int b) {
    return a < b ? a : b;
}

int spfa() {
    int i;
    for (i = s; i <= t; i++) {
        dis[i] = INF;
        pre[i] = -1;
        flow[i] = INF;
    }
    dis[s] = 0;
    flow[s] = INF;
    u[s] = s;
    v[s] = t;
    int head = 0, tail = 1;
    int que[MAXN];
    que[0] = s;
    while (head < tail) {
        int x = que[head++];
        for (i = 0; i < k[x]; i++) {
            int y = w[x * MAXN + i];
            if (flow[x] >= 1 && dis[y] > dis[x] + a[x] - b[y]) {
                dis[y] = dis[x] + a[x] - b[y];
                pre[y] = x;
                u[y] = x;
                v[y] = y;
                flow[y] = min(flow[x], c1[x]);
                if (y == t) {
                    while (y != s) {
                        x = pre[y];
                        flow[y] = min(flow[y], flow[x]);
                        y = x;
                    }
                    return 1;
                }
                que[tail++] = y;
            }
        }
    }
    return 0;
}

int main() {
    int i, j;
    scanf("%d", &n);
    s = 0;
    t = 2 * n + 1;
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }
    scanf("%d", &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &k[i], &c1[i], &c2[i]);
        for (j = 1; j <= k[i]; j++) {
            scanf("%d", &w[i * MAXN + j]);
        }
    }
    while (spfa()) {
        int x = t;
        ans += flow[t] * (a[u[x]] - b[v[x]]);
        while (x != s) {
            x = pre[x];
            a[x] -= flow[t];
            b[x] += flow[t];
        }
    }
    printf("%d\n", ans);
    return 0;
}