#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005
#define MAXM 600005
#define MAXQ 300005

int n, m, q;
int edges[MAXM][3];
int queries[MAXQ][2];
int parent[MAXN], rank[MAXN];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return;
    if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

int hasPuff(int x, int y) {
    while (x != y) {
        if (edges[find(x)][2] == 1) return 1;
        x = find(edges[x][1] == x ? edges[x][0] : edges[x][1]);
    }
    return edges[x][2] == 1;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &queries[i][0], &queries[i][1]);
    }

    init(n);

    for (int i = 0; i < m; i++) {
        union_sets(edges[i][0], edges[i][1]);
    }

    for (int i = 0; i < q; i++) {
        printf(hasPuff(queries[i][0], queries[i][1]) ? "YES\n" : "NO\n");
    }

    return 0;
}