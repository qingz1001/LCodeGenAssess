#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXQ 300005

typedef struct {
    int rank;
    int id;
} Island;

typedef struct {
    int parent;
    int size;
} UnionFind;

Island islands[MAXN];
UnionFind uf[MAXN];

int find(int x) {
    if (uf[x].parent != x) {
        uf[x].parent = find(uf[x].parent);
    }
    return uf[x].parent;
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return;
    if (uf[rootX].size < uf[rootY].size) {
        uf[rootX].parent = rootY;
        uf[rootY].size += uf[rootX].size;
    } else {
        uf[rootY].parent = rootX;
        uf[rootX].size += uf[rootY].size;
    }
}

void sortIslandsByRank(int n) {
    for (int i = 1; i <= n; i++) {
        islands[i].rank = i;
        islands[i].id = i;
    }
    qsort(islands + 1, n, sizeof(Island), [](const void *a, const void *b) {
        return ((Island *)b)->rank - ((Island *)a)->rank;
    });
}

int main() {
    int n, m, q;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &islands[i].rank);
        islands[i].id = i;
    }
    sortIslandsByRank(n);
    for (int i = 1; i <= n; i++) {
        uf[i].parent = i;
        uf[i].size = 1;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unionSets(u, v);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        char op;
        int x, y;
        scanf(" %c %d %d", &op, &x, &y);
        if (op == 'Q') {
            int root = find(x);
            if (y > uf[root].size) {
                printf("-1\n");
            } else {
                int count = 0;
                for (int j = 1; j <= n; j++) {
                    if (find(j) == root && ++count == y) {
                        printf("%d\n", islands[j].id);
                        break;
                    }
                }
            }
        } else if (op == 'B') {
            unionSets(x, y);
        }
    }
    return 0;
}