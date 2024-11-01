#include <stdio.h>
#include <stdlib.h>

#define MAX_N 205
#define MAX_W 6005
#define INF 1e9

int n, w;
int edges[MAX_W][3];
int parent[MAX_N];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    parent[find(x)] = find(y);
}

int kruskal() {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    int total_cost = 0;
    int edge_count = 0;

    for (int i = 0; i < w; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int cost = edges[i][2];

        if (find(u) != find(v)) {
            union_sets(u, v);
            total_cost += cost;
            edge_count++;
            if (edge_count == n - 1) {
                break;
            }
        }
    }

    if (edge_count < n - 1) {
        return -1;
    }

    return total_cost;
}

int main() {
    scanf("%d %d", &n, &w);

    for (int i = 0; i < w; i++) {
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    }

    printf("%d\n", kruskal());

    return 0;
}