#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005

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

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    init(n);

    int last = 0;
    for (int i = 0; i < m; ++i) {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);

        x ^= last;
        y ^= last;

        if (op == 0) {
            union_sets(x, y);
        } else if (op == 1) {
            if (find(x) == find(y)) {
                printf("Y\n");
                last = x;
            } else {
                printf("N\n");
                last = y;
            }
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