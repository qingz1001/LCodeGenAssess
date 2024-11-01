#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MAXM 20000

typedef struct {
    int a, b, c1, c2, idx;
} Road;

Road roads[MAXM];
int parent[MAXN + 1];
int rank[MAXN + 1];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_set(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int compare_roads(const void *a, const void *b) {
    Road *roadA = (Road *)a;
    Road *roadB = (Road *)b;
    if (roadA->c1 != roadB->c1) {
        return roadA->c1 - roadB->c1;
    } else {
        return roadA->c2 - roadB->c2;
    }
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

    qsort(roads, m, sizeof(Road), compare_roads);

    int max_cost = 0;
    int selected_roads[n - 1];
    int selected_types[n - 1];
    int selected_count = 0;

    for (int i = 0; i < m && selected_count < n - 1; i++) {
        int a = roads[i].a;
        int b = roads[i].b;
        int c1 = roads[i].c1;
        int c2 = roads[i].c2;
        int idx = roads[i].idx;

        if (find(a) != find(b)) {
            union_set(a, b);
            selected_roads[selected_count] = idx;
            selected_types[selected_count] = (selected_count < k) ? 1 : 2;
            max_cost = (selected_count < k) ? c1 : c2;
            selected_count++;
        }
    }

    printf("%d\n", max_cost);
    for (int i = 0; i < n - 1; i++) {
        printf("%d %d\n", selected_roads[i], selected_types[i]);
    }

    return 0;
}