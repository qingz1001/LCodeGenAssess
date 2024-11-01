#include <stdio.h>
#include <stdlib.h>

#define MAXN 20005
#define MAXM 100005

typedef struct {
    int a, b, c;
} Edge;

int parent[MAXN], rank[MAXN];
Edge edges[MAXM];

int cmp(const void *a, const void *b) {
    return ((Edge *)b)->c - ((Edge *)a)->c;
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
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].c);
    }

    qsort(edges, M, sizeof(Edge), cmp);

    for (int i = 0; i < M; i++) {
        int rootA = find(edges[i].a);
        int rootB = find(edges[i].b);
        if (rootA == rootB) {
            printf("%d\n", edges[i].c);
            return 0;
        }
        union_set(edges[i].a, edges[i].b + N);
        union_set(edges[i].b, edges[i].a + N);
    }

    printf("0\n");
    return 0;
}