#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXE 500005

typedef struct {
    int u, v;
} Edge;

Edge edges[MAXE];
int parent[MAXN], depth[MAXN], heavy[MAXN], head[MAXN], pos[MAXN], subtree_size[MAXN], euler_tour[MAXN], euler_depth[MAXN], euler_index = 0;
int n, m, q, euler_tour_size = 0;

void dfs(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    subtree_size[u] = 1;
    for (int i = head[u]; i != -1; i = heavy[i]) {
        dfs(heavy[i], u);
        subtree_size[u] += subtree_size[heavy[i]];
    }
}

void decompose(int u, int h) {
    head[u] = h;
    pos[u] = euler_tour_size;
    euler_tour[euler_tour_size++] = u;
    euler_depth[pos[u]] = depth[u];
    int max_size = 0, max_index = -1;
    for (int i = head[u]; i != -1; i = heavy[i]) {
        if (subtree_size[heavy[i]] > max_size) {
            max_size = subtree_size[heavy[i]];
            max_index = i;
        }
    }
    if (max_index != -1) {
        decompose(heavy[u], h);
    }
    for (int i = head[u]; i != -1; i = heavy[i]) {
        if (i != max_index) {
            decompose(heavy[i], i);
        }
    }
}

void build_lca() {
    dfs(1, 0);
    decompose(1, -1);
}

int lca(int u, int v) {
    while (head[u] != head[v]) {
        if (depth[euler_tour[pos[u]]] > depth[euler_tour[pos[v]]]) {
            u = parent[euler_tour[pos[u]]];
        } else {
            v = parent[euler_tour[pos[v]]];
        }
    }
    if (depth[u] > depth[v]) {
        return v;
    } else {
        return u;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
        edges[i].u--;
        edges[i].v--;
        heavy[edges[i].u] = head[edges[i].v];
        head[edges[i].u] = i;
        heavy[edges[i].v] = head[edges[i].u];
        head[edges[i].v] = i;
    }
    build_lca();
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int A, B, G1, G2;
            scanf("%d %d %d %d", &A, &B, &G1, &G2);
            A--;
            B--;
            G1--;
            G2--;
            if (lca(A, B) != lca(G1, G2)) {
                printf("yes\n");
            } else {
                printf("no\n");
            }
        } else if (type == 2) {
            int A, B, C;
            scanf("%d %d %d", &A, &B, &C);
            A--;
            B--;
            C--;
            if (lca(A, B) != C) {
                printf("yes\n");
            } else {
                printf("no\n");
            }
        }
    }
    return 0;
}