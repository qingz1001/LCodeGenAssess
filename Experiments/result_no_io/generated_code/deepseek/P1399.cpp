#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#define MAXN 100005

typedef struct {
    int to, next;
    double len;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
double dist[MAXN];

void add_edge(int u, int v, double len) {
    edges[edge_count].to = v;
    edges[edge_count].len = len;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int node, int parent) {
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to == parent) continue;
        dist[to] = dist[node] + edges[i].len;
        dfs(to, node);
    }
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) head[i] = -1;

    for (int i = 1; i < N; i++) {
        int A, B;
        double L;
        scanf("%d %d %lf", &A, &B, &L);
        add_edge(A, B, L);
        add_edge(B, A, L);
    }

    // Find the farthest node from node 1
    dist[1] = 0;
    dfs(1, -1);
    int farthest_node = 1;
    double max_dist = 0;
    for (int i = 1; i <= N; i++) {
        if (dist[i] > max_dist) {
            max_dist = dist[i];
            farthest_node = i;
        }
    }

    // Find the farthest node from the farthest node found above
    dist[farthest_node] = 0;
    dfs(farthest_node, -1);
    max_dist = 0;
    for (int i = 1; i <= N; i++) {
        if (dist[i] > max_dist) {
            max_dist = dist[i];
        }
    }

    // The result is the diameter of the tree divided by 2
    printf("%.1f\n", max_dist / 2);

    return 0;
}