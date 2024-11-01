#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 300005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to, weight;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
int parent[MAX_N];
int rank[MAX_N];
int max_weight[MAX_N][20];
int depth[MAX_N];
int log_table[MAX_N];

void add_edge(int from, int to, int weight) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->weight = weight;
    e->next = graph[from];
    graph[from] = e;
}

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        if (rank[x] == rank[y])
            rank[x]++;
    }
}

void dfs(int u, int p, int w) {
    depth[u] = depth[p] + 1;
    max_weight[u][0] = w;
    for (int i = 1; i < 20; i++) {
        max_weight[u][i] = max_weight[max_weight[u][i-1]][i-1];
    }
    for (Edge* e = graph[u]; e; e = e->next) {
        if (e->to != p) {
            dfs(e->to, u, e->weight);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    int diff = depth[u] - depth[v];
    for (int i = 19; i >= 0; i--) {
        if ((diff & (1 << i)) != 0) {
            u = max_weight[u][i];
        }
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if (max_weight[u][i] != max_weight[v][i]) {
            u = max_weight[u][i];
            v = max_weight[v][i];
        }
    }
    return max_weight[u][0];
}

int query(int u, int v) {
    int l = lca(u, v);
    int result = 0;
    while (u != l) {
        result = result > max_weight[u][0] ? result : max_weight[u][0];
        u = max_weight[u][0];
    }
    while (v != l) {
        result = result > max_weight[v][0] ? result : max_weight[v][0];
        v = max_weight[v][0];
    }
    return result;
}

int main() {
    int n, m, q;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        if (find(a) != find(b)) {
            unite(a, b);
            add_edge(a, b, l);
            add_edge(b, a, l);
        }
    }

    dfs(1, 0, 0);

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (find(a) != find(b)) {
            printf("impossible\n");
        } else {
            printf("%d\n", query(a, b));
        }
    }

    return 0;
}