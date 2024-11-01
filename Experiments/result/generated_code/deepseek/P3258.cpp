#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005

typedef struct Edge {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], cnt = 0;
int candy[MAXN], visit[MAXN];
int path[MAXN];

void addEdge(int u, int v) {
    edges[cnt].to = v;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u, int parent) {
    visit[u]++;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != parent) {
            dfs(v, u);
            visit[u] += visit[v];
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &path[i]);
    }
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        addEdge(x, y);
        addEdge(y, x);
    }

    dfs(path[1], -1);

    for (int i = 1; i < n; i++) {
        candy[path[i]]++;
    }

    for (int i = 1; i <= n; i++) {
        printf("%d\n", candy[i] + visit[i] - 1);
    }

    return 0;
}