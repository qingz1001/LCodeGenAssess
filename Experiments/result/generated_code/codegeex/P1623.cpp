#include <stdio.h>
#include <string.h>

int n, head[1005], cnt, match[1005], vis[1005];
struct Edge {
    int to, nxt;
} edge[2005];

void add(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

int dfs(int u, int v) {
    int i, x;
    for (i = head[u]; i; i = edge[i].nxt) {
        x = edge[i].to;
        if (x != v && x != match[u] && !vis[x]) {
            vis[x] = 1;
            if (!match[x] || dfs(match[x], x)) {
                match[u] = x;
                match[x] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int i, j, x, y, sum = 0, ans = 1;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        while (y--) {
            scanf("%d", &j);
            add(x, j);
            add(j, x);
        }
    }
    for (i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i, 0)) sum++;
    }
    printf("%d\n", sum);
    for (i = 1; i <= n; i++) {
        match[i] = 0;
    }
    for (i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i, 0)) ans++;
    }
    printf("%d\n", ans);
    return 0;
}