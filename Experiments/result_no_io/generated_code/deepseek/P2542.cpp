#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 30005
#define MAXM 100005

typedef struct {
    int u, v;
} Edge;

typedef struct {
    int type, u, v;
} Operation;

int n, m;
Edge edges[MAXM];
Operation ops[MAXM];
int parent[MAXN], rank[MAXN];

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
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
        union_sets(edges[i].u, edges[i].v);
    }

    int op_count = 0;
    while (1) {
        int op;
        scanf("%d", &op);
        if (op == -1) break;
        ops[op_count].type = op;
        scanf("%d %d", &ops[op_count].u, &ops[op_count].v);
        op_count++;
    }

    for (int i = 0; i < op_count; i++) {
        if (ops[i].type == 1) {
            if (find(ops[i].u) == find(ops[i].v)) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        } else if (ops[i].type == 0) {
            union_sets(ops[i].u, ops[i].v);
        }
    }

    return 0;
}