#include <stdio.h>
#include <stdbool.h>

#define MAXN 501
#define MAXM 1002

int parent[MAXN];
int rank[MAXN];

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

bool has_cycle(int n, int edges[][2], int m) {
    init(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        if (find(u) == find(v)) {
            return true;
        }
        union_sets(u, v);
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        int edges[MAXM][2];
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &edges[i][0], &edges[i][1]);
        }

        if (has_cycle(n, edges, m)) {
            printf("No\n");
        } else {
            printf("Yes\n");
        }
    }
    return 0;
}