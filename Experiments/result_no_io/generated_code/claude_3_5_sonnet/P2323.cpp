#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 20001

typedef struct {
    int a, b, c1, c2;
} Road;

typedef struct {
    int parent;
    int rank;
} DisjointSet;

Road roads[MAX_M];
DisjointSet sets[MAX_N];
int n, k, m;
int selected[MAX_M];
int selected_count = 0;

int cmp(const void* a, const void* b) {
    return ((Road*)a)->c1 - ((Road*)b)->c1;
}

void init_set() {
    for (int i = 1; i <= n; i++) {
        sets[i].parent = i;
        sets[i].rank = 0;
    }
}

int find_set(int x) {
    if (sets[x].parent != x)
        sets[x].parent = find_set(sets[x].parent);
    return sets[x].parent;
}

void union_sets(int x, int y) {
    int px = find_set(x);
    int py = find_set(y);
    if (px == py) return;
    if (sets[px].rank < sets[py].rank)
        sets[px].parent = py;
    else if (sets[px].rank > sets[py].rank)
        sets[py].parent = px;
    else {
        sets[py].parent = px;
        sets[px].rank++;
    }
}

int kruskal() {
    int max_cost = 0;
    int first_class = 0;
    
    for (int i = 0; i < m && selected_count < n - 1; i++) {
        int pa = find_set(roads[i].a);
        int pb = find_set(roads[i].b);
        if (pa != pb) {
            union_sets(pa, pb);
            selected[selected_count++] = i;
            if (first_class < k) {
                max_cost = max_cost > roads[i].c1 ? max_cost : roads[i].c1;
                first_class++;
            } else {
                max_cost = max_cost > roads[i].c2 ? max_cost : roads[i].c2;
            }
        }
    }
    
    return max_cost;
}

int main() {
    scanf("%d %d %d", &n, &k, &m);
    for (int i = 0; i < m - 1; i++) {
        scanf("%d %d %d %d", &roads[i].a, &roads[i].b, &roads[i].c1, &roads[i].c2);
    }
    
    qsort(roads, m - 1, sizeof(Road), cmp);
    
    init_set();
    int max_cost = kruskal();
    
    printf("%d\n", max_cost);
    for (int i = 0; i < n - 1; i++) {
        int road_index = selected[i];
        int level = (i < k) ? 1 : 2;
        printf("%d %d\n", road_index + 1, level);
    }
    
    return 0;
}