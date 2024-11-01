#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_P 800
#define MAX_C 1450

typedef struct {
    int to, dist;
} Edge;

typedef struct {
    int size;
    Edge edges[MAX_C];
} Graph;

Graph graph[MAX_P + 1];
int cow_positions[500 + 1];
int dist[MAX_P + 1];
int visited[MAX_P + 1];

void add_edge(int from, int to, int dist) {
    graph[from].edges[graph[from].size].to = to;
    graph[from].edges[graph[from].size].dist = dist;
    graph[from].size++;
}

void dijkstra(int start, int P) {
    for (int i = 1; i <= P; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int i = 1; i <= P; i++) {
        int min_dist = INT_MAX, u = -1;
        for (int j = 1; j <= P; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int j = 0; j < graph[u].size; j++) {
            int v = graph[u].edges[j].to;
            int weight = graph[u].edges[j].dist;
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
}

int main() {
    int N, P, C;
    scanf("%d %d %d", &N, &P, &C);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &cow_positions[i]);
    }

    for (int i = 0; i < C; i++) {
        int A, B, D;
        scanf("%d %d %d", &A, &B, &D);
        add_edge(A, B, D);
        add_edge(B, A, D);
    }

    int min_total_dist = INT_MAX;
    for (int i = 1; i <= P; i++) {
        dijkstra(i, P);
        int total_dist = 0;
        for (int j = 1; j <= N; j++) {
            total_dist += dist[cow_positions[j]];
        }
        if (total_dist < min_total_dist) {
            min_total_dist = total_dist;
        }
    }

    printf("%d\n", min_total_dist);

    return 0;
}