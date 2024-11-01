#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MAX_M 100001

int parent[MAX_N];
int rank[MAX_N];

typedef struct {
    int x, y, t;
} Road;

Road roads[MAX_M];

int compare(const void* a, const void* b) {
    return ((Road*)a)->t - ((Road*)b)->t;
}

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
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
        if (rank[x] == rank[y])
            rank[x]++;
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &roads[i].x, &roads[i].y, &roads[i].t);
    }

    qsort(roads, M, sizeof(Road), compare);

    init(N);
    int connected = 1;
    int last_time = 0;

    for (int i = 0; i < M; i++) {
        unite(roads[i].x, roads[i].y);
        last_time = roads[i].t;

        int root = find(1);
        int all_connected = 1;
        for (int j = 2; j <= N; j++) {
            if (find(j) != root) {
                all_connected = 0;
                break;
            }
        }

        if (all_connected) {
            connected = 1;
            break;
        }
    }

    if (connected) {
        printf("%d\n", last_time);
    } else {
        printf("-1\n");
    }

    return 0;
}