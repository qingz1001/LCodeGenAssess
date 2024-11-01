#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define MAXM 20005

typedef struct {
    int a, b, c1, c2, idx;
} Road;

Road roads[MAXM];
int parent[MAXN], rank[MAXN];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
        else if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int compare_c1(const void *a, const void *b) {
    return ((Road *)a)->c1 - ((Road *)b)->c1;
}

int compare_c2(const void *a, const void *b) {
    return ((Road *)a)->c2 - ((Road *)b)->c2;
}

int main() {
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &roads[i].a, &roads[i].b, &roads[i].c1, &roads[i].c2);
        roads[i].idx = i + 1;
    }

    // Sort roads by c1 (cost of primary road)
    qsort(roads, m, sizeof(Road), compare_c1);

    int primary_count = 0;
    int max_cost = 0;
    Road selected_roads[MAXN];
    int selected_count = 0;

    // Select at least k primary roads
    for (int i = 0; i < m && primary_count < k; i++) {
        if (find(roads[i].a) != find(roads[i].b)) {
            union_set(roads[i].a, roads[i].b);
            selected_roads[selected_count++] = roads[i];
            primary_count++;
            if (roads[i].c1 > max_cost) max_cost = roads[i].c1;
        }
    }

    // Sort remaining roads by c2 (cost of secondary road)
    qsort(roads, m, sizeof(Road), compare_c2);

    // Select remaining roads to complete the MST
    for (int i = 0; i < m && selected_count < n - 1; i++) {
        if (find(roads[i].a) != find(roads[i].b)) {
            union_set(roads[i].a, roads[i].b);
            selected_roads[selected_count++] = roads[i];
            if (roads[i].c2 > max_cost) max_cost = roads[i].c2;
        }
    }

    // Output the result
    printf("%d\n", max_cost);
    for (int i = 0; i < n - 1; i++) {
        printf("%d %d\n", selected_roads[i].idx, selected_roads[i].c1 <= selected_roads[i].c2 ? 1 : 2);
    }

    return 0;
}