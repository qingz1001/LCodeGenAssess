#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define EPSILON 1e-9

typedef struct {
    int weight;
    int cost;
} Factory;

typedef struct {
    int u;
    int v;
} Edge;

int parent[MAX_N];
double rank[MAX_N];

void init(int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0.0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] > rank[y]) {
        parent[y] = x;
    } else {
        parent[x] = y;
        if (rank[x] == rank[y]) {
            rank[y]++;
        }
    }
}

double kruskal(int n, Edge edges[], Factory factories[]) {
    double total_weight = 0.0;
    double total_cost = 0.0;
    init(n);
    for (int i = 0; i < n - 1; ++i) {
        int u = edges[i].u - 1;
        int v = edges[i].v - 1;
        if (find(u) != find(v)) {
            union_sets(u, v);
            total_weight += factories[u].weight + factories[v].weight;
            total_cost += factories[u].cost + factories[v].cost;
        }
    }
    return total_weight / (total_cost + EPSILON);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    Factory factories[MAX_N];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &factories[i].weight);
    }
    for (int i = 0; i < N; ++i) {
        scanf("%d", &factories[i].cost);
    }
    Edge edges[N - 1];
    for (int i = 0; i < N - 1; ++i) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
    }

    double max_ratio = 0.0;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            Factory removed_factories[2] = {factories[i], factories[j]};
            factories[i].weight = 0;
            factories[i].cost = 0;
            factories[j].weight = 0;
            factories[j].cost = 0;
            double ratio = kruskal(N, edges, factories);
            if (ratio > max_ratio) {
                max_ratio = ratio;
            }
            factories[i] = removed_factories[0];
            factories[j] = removed_factories[1];
        }
    }

    printf("%.1f\n", max_ratio);

    return 0;
}