#include <stdio.h>
#include <stdlib.h>

#define MAXN 20000
#define MAXM 100000

typedef struct {
    int a, b, c;
} Edge;

int cmp(const void *a, const void *b) {
    return ((Edge *)b)->c - ((Edge *)a)->c;
}

int parent[MAXN + 1];
int rank[MAXN + 1];

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

    Edge edges[MAXM];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].c);
    }

    qsort(edges, M, sizeof(Edge), cmp);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < M; i++) {
        int a = edges[i].a;
        int b = edges[i].b;
        int c = edges[i].c;

        if (find(a) == find(b)) {
            printf("%d\n", c);
            return 0;
        }

        if (parent[a] == a) {
            parent[a] = -1;
        }
        if (parent[b] == b) {
            parent[b] = -1;
        }

        if (parent[a] == -1) {
            parent[a] = find(b);
        } else if (parent[b] == -1) {
            parent[b] = find(a);
        } else {
            union_set(a, b + N);
            union_set(b, a + N);
        }
    }

    printf("0\n");
    return 0;
}