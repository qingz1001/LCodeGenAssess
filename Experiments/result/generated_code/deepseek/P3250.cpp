#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

typedef struct {
    int type;
    int a, b, v, t;
} Event;

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count;

Event events[MAXM];
int n, m;

int depth[MAXN], parent[MAXN][20];
int requests[MAXN];
int max_importance[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int u, int p, int d) {
    depth[u] = d;
    parent[u][0] = p;
    for (int i = 1; i < 20; i++) {
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
    }
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    for (int i = 19; i >= 0; i--) {
        if (depth[parent[u][i]] >= depth[v]) {
            u = parent[u][i];
        }
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

void update_importance(int u, int v, int importance) {
    int l = lca(u, v);
    while (u != l) {
        max_importance[u] = importance;
        u = parent[u][0];
    }
    while (v != l) {
        max_importance[v] = importance;
        v = parent[v][0];
    }
    max_importance[l] = importance;
}

int main() {
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    edge_count = 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    dfs(1, 0, 0);

    for (int i = 0; i < m; i++) {
        int type;
        scanf("%d", &type);
        if (type == 0) {
            int a, b, v;
            scanf("%d %d %d", &a, &b, &v);
            events[i].type = type;
            events[i].a = a;
            events[i].b = b;
            events[i].v = v;
            events[i].t = i;
            update_importance(a, b, v);
        } else if (type == 1) {
            int t;
            scanf("%d", &t);
            events[i].type = type;
            events[i].t = t;
            int a = events[t].a, b = events[t].b, v = events[t].v;
            update_importance(a, b, -1);
        } else if (type == 2) {
            int x;
            scanf("%d", &x);
            events[i].type = type;
            events[i].a = x;
            int max_imp = -1;
            for (int j = 1; j <= n; j++) {
                if (max_importance[j] != -1 && j != x) {
                    max_imp = max_imp > max_importance[j] ? max_imp : max_importance[j];
                }
            }
            printf("%d\n", max_imp);
        }
    }

    return 0;
}