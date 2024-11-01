#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 7

typedef struct {
    int parent;
    int size;
} UnionFind;

UnionFind uf[MAXN * MAXM];

void init(int n, int m) {
    for (int i = 0; i < n * m; ++i) {
        uf[i].parent = i;
        uf[i].size = 1;
    }
}

int find(int x) {
    if (uf[x].parent != x) {
        uf[x].parent = find(uf[x].parent);
    }
    return uf[x].parent;
}

void unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return;
    if (uf[px].size > uf[py].size) {
        uf[px].parent = py;
        uf[py].size += uf[px].size;
    } else {
        uf[py].parent = px;
        uf[px].size += uf[py].size;
    }
}

int isBuilding(char c) {
    return c == 'O';
}

int isValid(int i, int j, int n, int m) {
    return i >= 0 && i < n && j >= 0 && j < m;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[n][MAXM];
    for (int i = 0; i < n; ++i) {
        scanf("%s", grid[i]);
    }

    init(n, m);

    int q;
    scanf("%d", &q);
    while (q--) {
        char op;
        int i, j, k;
        scanf(" %c", &op);
        if (op == 'C') {
            scanf("%d %d %c", &i, &j, &k);
            --i, --j;
            int idx = i * m + j;
            if (isBuilding(grid[i][j])) {
                int oldParent = find(idx);
                uf[oldParent].size--;
            }
            grid[i][j] = k;
            if (isBuilding(k)) {
                int newParent = find(idx);
                uf[newParent].size++;
            }
            if (isValid(i - 1, j, n, m) && isBuilding(grid[i - 1][j]) && isBuilding(k)) {
                unite(idx, idx - m);
            }
            if (isValid(i + 1, j, n, m) && isBuilding(grid[i + 1][j]) && isBuilding(k)) {
                unite(idx, idx + m);
            }
            if (isValid(i, j - 1, n, m) && isBuilding(grid[i][j - 1]) && isBuilding(k)) {
                unite(idx, idx - 1);
            }
            if (isValid(i, j + 1, n, m) && isBuilding(grid[i][j + 1]) && isBuilding(k)) {
                unite(idx, idx + 1);
            }
        } else if (op == 'Q') {
            int l, r;
            scanf("%d %d", &l, &r);
            --l, --r;
            int count = 0;
            for (int i = l; i <= r; ++i) {
                if (find(i * m) == i * m) count++;
            }
            printf("%d\n", count);
        }
    }

    return 0;
}