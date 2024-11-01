#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 300005

typedef struct {
    int p;
    int id;
} Island;

int parent[MAXN];
int rank[MAXN];
Island islands[MAXN];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
        islands[i].id = i;
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

void updateRank(int root) {
    for (int i = 1; i <= MAXN; i++) {
        if (find(i) == root) {
            islands[i].p = rank[root];
        }
    }
}

int query(int x, int k) {
    int root = find(x);
    if (islands[root].p < k) return -1;
    int count = 0;
    for (int i = 1; i <= MAXN; i++) {
        if (find(i) == root && islands[i].p == k) {
            return islands[i].id;
        }
    }
    return -1;
}

int main() {
    int n, m, q;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &islands[i].p);
    }
    init(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unionSets(u, v);
        updateRank(find(u));
    }
    scanf("%d", &q);
    while (q--) {
        char op;
        int x, y;
        scanf(" %c %d %d", &op, &x, &y);
        if (op == 'Q') {
            printf("%d\n", query(x, y));
        } else if (op == 'B') {
            unionSets(x, y);
            updateRank(find(x));
        }
    }
    return 0;
}