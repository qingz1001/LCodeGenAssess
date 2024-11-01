#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_LOG 17

int n, m;
int weight[MAX_N];
int parent[MAX_N][MAX_LOG];
int depth[MAX_N];
int sorted_weight[MAX_N];
int pos[MAX_N];
int tree_size[MAX_N];

struct Edge {
    int to, next;
} edge[MAX_N * 2];

int head[MAX_N], edge_cnt;

void add_edge(int u, int v) {
    edge[++edge_cnt] = (struct Edge){v, head[u]};
    head[u] = edge_cnt;
}

int cmp(const void *a, const void *b) {
    return weight[*(int*)a] - weight[*(int*)b];
}

void dfs(int u, int p, int d) {
    depth[u] = d;
    parent[u][0] = p;
    tree_size[u] = 1;

    for (int i = 1; i < MAX_LOG; i++) {
        parent[u][i] = parent[parent[u][i-1]][i-1];
    }

    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v != p) {
            dfs(v, u, d + 1);
            tree_size[u] += tree_size[v];
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }

    for (int i = MAX_LOG - 1; i >= 0; i--) {
        if (depth[parent[u][i]] >= depth[v]) {
            u = parent[u][i];
        }
    }

    if (u == v) return u;

    for (int i = MAX_LOG - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

int query(int u, int v, int k) {
    int ancestor = lca(u, v);
    int left = depth[u] - depth[ancestor] + 1;
    int right = depth[v] - depth[ancestor] + 1;
    int total = left + right - 1;

    if (k > total) return -1;

    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        int count = 0;
        int temp_u = u, temp_v = v;

        while (temp_u != ancestor) {
            if (pos[temp_u] <= mid) count++;
            temp_u = parent[temp_u][0];
        }

        while (temp_v != ancestor) {
            if (pos[temp_v] <= mid) count++;
            temp_v = parent[temp_v][0];
        }

        if (pos[ancestor] <= mid) count++;

        if (count >= k) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    return weight[sorted_weight[l]];
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &weight[i]);
        sorted_weight[i] = i;
    }

    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }

    dfs(1, 0, 1);

    qsort(sorted_weight + 1, n, sizeof(int), cmp);
    for (int i = 1; i <= n; i++) {
        pos[sorted_weight[i]] = i;
    }

    int last = 0;
    for (int i = 0; i < m; i++) {
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        u ^= last;
        last = query(u, v, k);
        printf("%d\n", last);
    }

    return 0;
}