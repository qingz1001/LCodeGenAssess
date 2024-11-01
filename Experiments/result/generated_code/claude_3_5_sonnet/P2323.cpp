#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 20001

typedef struct {
    int a, b, c1, c2;
} Road;

Road roads[MAX_M];
int parent[MAX_N];
int rank[MAX_N];
int n, k, m;

int cmp(const void *a, const void *b) {
    return ((Road*)a)->c1 - ((Road*)b)->c1;
}

void init_set() {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
    int px = find_set(x);
    int py = find_set(y);
    if (rank[px] < rank[py])
        parent[px] = py;
    else if (rank[px] > rank[py])
        parent[py] = px;
    else {
        parent[py] = px;
        rank[px]++;
    }
}

int main() {
    scanf("%d %d %d", &n, &k, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &roads[i].a, &roads[i].b, &roads[i].c1, &roads[i].c2);
    }

    qsort(roads, m, sizeof(Road), cmp);

    int max_cost = 0;
    int first_class = 0;
    int total_roads = 0;
    int result[MAX_N][2];

    init_set();

    for (int i = 0; i < m && total_roads < n - 1; i++) {
        int a = roads[i].a;
        int b = roads[i].b;
        if (find_set(a) != find_set(b)) {
            union_sets(a, b);
            int cost, level;
            if (first_class < k) {
                cost = roads[i].c1;
                level = 1;
                first_class++;
            } else {
                cost = roads[i].c2;
                level = 2;
            }
            if (cost > max_cost) max_cost = cost;
            result[total_roads][0] = i + 1;
            result[total_roads][1] = level;
            total_roads++;
        }
    }

    printf("%d\n", max_cost);
    for (int i = 0; i < n - 1; i++) {
        printf("%d %d\n", result[i][0], result[i][1]);
    }

    return 0;
}