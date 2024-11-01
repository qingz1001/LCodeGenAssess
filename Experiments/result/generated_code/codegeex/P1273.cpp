#include <stdio.h>
#include <string.h>

#define MAXN 3001

int n, m, k, a, c, f[MAXN][MAXN], w[MAXN];

struct Edge {
    int v, c, next;
} e[MAXN];

int head[MAXN], tot;

void add(int u, int v, int c) {
    e[++tot].v = v;
    e[tot].c = c;
    e[tot].next = head[u];
    head[u] = tot;
}

int dp(int u, int t) {
    if (f[u][t] != -1) return f[u][t];
    if (u > n - m) return w[u] >= t ? 1 : 0;
    int ans = 0;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].v, c = e[i].c;
        ans += dp(v, t - c);
    }
    return f[u][t] = ans;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, 0, sizeof(head));
    tot = 0;
    memset(f, -1, sizeof(f));
    for (int i = 1; i <= n - m; i++) {
        scanf("%d", &k);
        for (int j = 1; j <= k; j++) {
            scanf("%d%d", &a, &c);
            add(i, a, c);
        }
    }
    for (int i = n - m + 1; i <= n; i++) scanf("%d", &w[i]);
    for (int t = m; t >= 0; t--) {
        if (dp(1, t) >= t) {
            printf("%d\n", t);
            break;
        }
    }
    return 0;
}