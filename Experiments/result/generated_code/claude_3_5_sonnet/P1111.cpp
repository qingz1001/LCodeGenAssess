#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MAX_M 100001

typedef struct {
    int x, y, t;
} Road;

int parent[MAX_N];
Road roads[MAX_M];

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py) parent[px] = py;
}

int cmp(const void *a, const void *b) {
    return ((Road*)a)->t - ((Road*)b)->t;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &roads[i].x, &roads[i].y, &roads[i].t);
    }

    qsort(roads, M, sizeof(Road), cmp);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    int components = N;
    int last_time = 0;

    for (int i = 0; i < M; i++) {
        int x = roads[i].x;
        int y = roads[i].y;
        int t = roads[i].t;

        if (find(x) != find(y)) {
            unite(x, y);
            components--;
            last_time = t;
        }

        if (components == 1) {
            printf("%d\n", last_time);
            return 0;
        }
    }

    printf("-1\n");
    return 0;
}