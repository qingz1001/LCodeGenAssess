#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 10005
#define MAXM 20005

int n, m;
int head[MAXN], to[MAXM * 2], next[MAXM * 2], idx;
bool vis[MAXN];
int color[MAXN];

void addEdge(int u, int v) {
    to[idx] = v;
    next[idx] = head[u];
    head[u] = idx++;
}

bool dfs(int u, int c) {
    vis[u] = true;
    color[u] = c;
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = to[i];
        if (vis[v]) {
            if (color[v] == c) return false;
        } else {
            if (!dfs(v, 1 - c)) return false;
        }
    }
    return true;
}

bool isBipartite() {
    memset(vis, false, sizeof(vis));
    memset(color, -1, sizeof(color));
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            if (!dfs(i, 0)) return false;
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        memset(head, -1, sizeof(head));
        idx = 0;
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        if (isBipartite()) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}