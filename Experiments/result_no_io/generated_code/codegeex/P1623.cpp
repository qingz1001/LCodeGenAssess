#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int n, cnt, head[MAXN], vis[MAXN], match[MAXN];
struct Edge {
    int to, next;
} edge[MAXN << 1];

void addEdge(int u, int v) {
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

int dfs(int u) {
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (!vis[v]) {
            vis[v] = 1;
            if (!match[v] || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) head[i] = -1;
    for (int i = 1; i <= n; i++) {
        int id, m, v;
        scanf("%d%d", &id, &m);
        while (m--) {
            scanf("%d", &v);
            addEdge(id, v);
        }
    }

    int maxMatch = 0, maxMatchCount = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) vis[j] = 0;
        if (dfs(i)) maxMatch++;
    }

    printf("%d\n", maxMatch);

    for (int i = 1; i <= n; i++) match[i] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) vis[j] = 0;
        if (dfs(i)) maxMatchCount++;
    }

    printf("%d\n", maxMatchCount);

    return 0;
}