#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 300005
#define MAXQ 100005

struct Edge {
    int u, v, w;
};

int parent[MAXN];
int size[MAXN];

int compare(const void *a, const void *b) {
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    return edgeA->w - edgeB->w;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (size[rootX] < size[rootY]) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        } else {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    struct Edge edges[MAXM];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, M, sizeof(struct Edge), compare);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    int Q;
    scanf("%d", &Q);

    int results[MAXQ];
    for (int i = 0; i < Q; i++) {
        int A, B;
        scanf("%d %d", &A, &B);
        results[i] = -1;
    }

    for (int i = 0; i < M; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (find(u) != find(v)) {
            unite(u, v);
            for (int j = 0; j < Q; j++) {
                int A = results[j];
                int B = results[j];
                if (A != -1 && B != -1 && find(A) == find(B)) {
                    results[j] = w;
                }
            }
        }
    }

    for (int i = 0; i < Q; i++) {
        if (results[i] == -1) {
            printf("impossible\n");
        } else {
            printf("%d\n", results[i]);
        }
    }

    return 0;
}