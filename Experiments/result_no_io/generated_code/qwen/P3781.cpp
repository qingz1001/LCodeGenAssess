#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

typedef struct Node {
    int value;
    int size;
    int xorSum;
} Node;

Node tree[10005];
int parent[10005];
int rank[10005];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        tree[i].value = 0;
        tree[i].size = 1;
        tree[i].xorSum = 0;
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (rank[u] > rank[v]) {
        parent[v] = u;
        tree[u].xorSum ^= tree[v].xorSum;
    } else {
        parent[u] = v;
        tree[v].xorSum ^= tree[u].xorSum;
        if (rank[u] == rank[v]) {
            rank[v]++;
        }
    }
    tree[u].size += tree[v].size;
}

void update(int u, int newValue) {
    int oldXorSum = tree[u].xorSum;
    tree[u].value = newValue;
    tree[u].xorSum = oldXorSum ^ newValue;
    while (u != find(u)) {
        u = find(u);
        tree[u].xorSum = tree[u].xorSum ^ oldXorSum ^ newValue;
        oldXorSum = newValue;
        newValue = tree[u].value;
    }
}

int query(int k) {
    int count = 0;
    for (int i = 1; i <= 10000; i++) {
        if (tree[i].xorSum == k) {
            count++;
        }
    }
    return count % MOD;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    init(n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &tree[i].value);
        tree[i].xorSum = tree[i].value;
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        merge(a, b);
    }

    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        char op[10];
        int x, y, k;
        scanf("%s", op);
        if (op[0] == 'C') {
            scanf("%d %d", &x, &y);
            update(x, y);
        } else if (op[0] == 'Q') {
            scanf("%d", &k);
            printf("%d\n", query(k));
        }
    }

    return 0;
}