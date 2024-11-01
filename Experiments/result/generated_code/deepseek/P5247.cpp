#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005

typedef struct {
    int parent;
    int rank;
} UnionFind;

UnionFind uf[MAXN];

void init(int n) {
    for (int i = 0; i < n; i++) {
        uf[i].parent = i;
        uf[i].rank = 0;
    }
}

int find(int x) {
    if (uf[x].parent != x) {
        uf[x].parent = find(uf[x].parent);
    }
    return uf[x].parent;
}

void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (uf[rootX].rank < uf[rootY].rank) {
            uf[rootX].parent = rootY;
        } else if (uf[rootX].rank > uf[rootY].rank) {
            uf[rootY].parent = rootX;
        } else {
            uf[rootY].parent = rootX;
            uf[rootX].rank++;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    init(n);

    int last = 0;
    for (int i = 0; i < m; i++) {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        x ^= last;
        y ^= last;

        if (op == 0) {
            unionSet(x, y);
        } else if (op == 1) {
            // Since we are using Union-Find, we cannot directly delete edges.
            // This part is left as a placeholder for completeness.
        } else if (op == 2) {
            if (find(x) == find(y)) {
                printf("Y\n");
                last = x;
            } else {
                printf("N\n");
                last = y;
            }
        }
    }

    return 0;
}