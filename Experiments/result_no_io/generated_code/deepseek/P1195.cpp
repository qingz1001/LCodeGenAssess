#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define MAXM 10005

typedef struct {
    int x, y, l;
} Edge;

int parent[MAXN];
Edge edges[MAXM];

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->l - ((Edge *)b)->l;
}

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py) parent[px] = py;
}

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 1; i <= N; i++) parent[i] = i;

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].l);
    }

    qsort(edges, M, sizeof(Edge), cmp);

    int count = N;
    int total_cost = 0;

    for (int i = 0; i < M; i++) {
        int x = edges[i].x;
        int y = edges[i].y;
        int l = edges[i].l;

        if (find(x) != find(y)) {
            union_set(x, y);
            total_cost += l;
            count--;
        }

        if (count == K) break;
    }

    if (count == K) {
        printf("%d\n", total_cost);
    } else {
        printf("No Answer\n");
    }

    return 0;
}