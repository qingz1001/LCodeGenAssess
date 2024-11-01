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

bool union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) {
        return false;
    }
    if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    return true;
}

bool solve(int n, int m, int edges[][2]) {
    init(n);
    for (int i = 0; i < m; i++) {
        if (!union_sets(edges[i][0], edges[i][1])) {
            return false;
        }
    }
    return true;
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
        if (solve(n, m, edges)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}