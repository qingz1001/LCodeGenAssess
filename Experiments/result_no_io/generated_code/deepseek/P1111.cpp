#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 100005

typedef struct {
    int x, y, t;
} Edge;

int parent[MAXN];
Edge edges[MAXM];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->t - ((Edge *)b)->t;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].t);
    }

    qsort(edges, M, sizeof(Edge), cmp);

    for (int i = 0; i < M; i++) {
        unionSet(edges[i].x, edges[i].y);
        int root = find(1);
        int connected = 1;
        for (int j = 2; j <= N; j++) {
            if (find(j) != root) {
                connected = 0;
                break;
            }
        }
        if (connected) {
            printf("%d\n", edges[i].t);
            return 0;
        }
    }

    printf("-1\n");
    return 0;
}