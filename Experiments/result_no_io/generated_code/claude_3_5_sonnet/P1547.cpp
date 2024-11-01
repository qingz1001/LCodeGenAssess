#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000
#define MAX_M 10000

typedef struct {
    int a, b, l;
} Edge;

int parent[MAX_N + 1];
Edge edges[MAX_M];

int compare(const void* a, const void* b) {
    return ((Edge*)a)->l - ((Edge*)b)->l;
}

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    parent[find(x)] = find(y);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].l);
    }

    qsort(edges, M, sizeof(Edge), compare);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    int max_length = 0;
    int connected = 0;

    for (int i = 0; i < M && connected < N - 1; i++) {
        int a = edges[i].a;
        int b = edges[i].b;
        if (find(a) != find(b)) {
            unite(a, b);
            connected++;
            if (edges[i].l > max_length) {
                max_length = edges[i].l;
            }
        }
    }

    printf("%d\n", max_length);

    return 0;
}