#include <stdio.h>
#include <stdlib.h>

#define MAXN 150
#define MAXM 5000

int parent[MAXN];
int rank[MAXN];

void init(int n) {
    for (int i = 0; i <= n; i++) {
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
    int n, m;
    scanf("%d %d", &n, &m);

    init(n);

    int edges[MAXM][2];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i][0], &edges[i][1]);
    }

    for (int i = 0; i < m; i++) {
        int x = edges[i][0];
        int y = edges[i][1];
        int originalParentX = find(x);
        int originalParentY = find(y);
        union_sets(x, y);
        for (int j = 0; j < m; j++) {
            if (j == i) continue;
            int a = edges[j][0];
            int b = edges[j][1];
            if (find(a) != find(b)) {
                printf("%d %d\n", x, y);
                goto end;
            }
        }
        init(n);
        union_sets(originalParentX, originalParentY);
    }

end:
    return 0;
}