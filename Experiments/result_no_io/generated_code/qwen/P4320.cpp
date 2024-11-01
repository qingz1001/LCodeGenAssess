#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int parent[MAXN];
int rank[MAXN];

void init(int n) {
    for (int i = 0; i <= n; ++i) {
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
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int main() {
    int n, m, q;
    scanf("%d %d", &n, &m);
    init(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        union_sets(u, v);
    }

    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (find(u) == find(v)) {
            printf("2\n");
        } else {
            printf("1\n");
        }
    }

    return 0;
}