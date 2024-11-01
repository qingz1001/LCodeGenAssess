#include <stdio.h>
#include <stdlib.h>

#define MAXN 5001

int parent[MAXN];

void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
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
            unionSets(x, y);
        } else if (op == 1) {
            unionSets(x, y);
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