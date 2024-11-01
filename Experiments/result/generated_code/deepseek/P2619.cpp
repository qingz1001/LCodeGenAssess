#include <stdio.h>
#include <stdlib.h>

#define MAXV 50000
#define MAXE 100000

typedef struct {
    int s, t, c, col;
} Edge;

int V, E, need;
Edge edges[MAXE];
int parent[MAXV];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py) parent[px] = py;
}

int cmp(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    if (e1->col == e2->col) return e1->c - e2->c;
    return e1->col - e2->col;
}

int kruskal() {
    for (int i = 0; i < V; i++) parent[i] = i;
    qsort(edges, E, sizeof(Edge), cmp);

    int white_count = 0, total_cost = 0;
    for (int i = 0; i < E; i++) {
        int s = edges[i].s, t = edges[i].t, c = edges[i].c, col = edges[i].col;
        if (find(s) != find(t)) {
            union_set(s, t);
            total_cost += c;
            if (col == 0) white_count++;
            if (white_count == need) break;
        }
    }
    return total_cost;
}

int main() {
    scanf("%d %d %d", &V, &E, &need);
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d %d", &edges[i].s, &edges[i].t, &edges[i].c, &edges[i].col);
    }
    printf("%d\n", kruskal());
    return 0;
}