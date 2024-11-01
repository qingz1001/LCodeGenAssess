#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int parent[MAXN];
int rank[MAXN];

void init(int size) {
    for (int i = 0; i < size; ++i) {
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

void union_set(int x, int y) {
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
    scanf("%d %d", &n, &m);
    init(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        union_set(u, v);
    }

    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (find(i) == i) {
            count++;
        }
    }

    printf("%d\n", count - 1);

    return 0;
}