#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005
#define MAXM 500005

int n, m;
int last = 0;
int edges[MAXM][2];
int parent[MAXN];

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
        parent[rootX] = rootY;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        x ^= last;
        y ^= last;

        if (op == 0) {
            union_sets(x, y);
        } else if (op == 1) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX == rootY) {
                printf("Y\n");
            } else {
                printf("N\n");
            }
        } else if (op == 2) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX == rootY) {
                last = x;
            } else {
                last = y;
            }
        }
    }

    return 0;
}