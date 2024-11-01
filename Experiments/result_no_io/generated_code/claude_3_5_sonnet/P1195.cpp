#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1005
#define MAX_M 10005
#define INF 0x3f3f3f3f

int parent[MAX_N];
int rank[MAX_N];

typedef struct {
    int x, y, l;
} Edge;

Edge edges[MAX_M];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
}

int cmp(const void* a, const void* b) {
    return ((Edge*)a)->l - ((Edge*)b)->l;
}

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].l);
    }

    qsort(edges, M, sizeof(Edge), cmp);

    int min_cost = 0;
    int components = N;

    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < M && components > K; i++) {
        int x = find(edges[i].x - 1);
        int y = find(edges[i].y - 1);
        if (x != y) {
            unite(x, y);
            min_cost += edges[i].l;
            components--;
        }
    }

    if (components == K) {
        printf("%d\n", min_cost);
    } else {
        printf("No Answer\n");
    }

    return 0;
}