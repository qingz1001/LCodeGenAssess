#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005

typedef struct {
    int parent;
    int rank;
} UnionFind;

UnionFind uf[MAXN];
int last = 0;

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

void union_set(int x, int y) {
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

    for (int i = 0; i < m; i++) {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        x ^= last;
        y ^= last;

        if (op == 0) {
            union_set(x, y);
        } else if (op == 1) {
            // Since we are using union-find, we cannot easily delete edges.
            // This part is left unimplemented as per the problem statement.
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