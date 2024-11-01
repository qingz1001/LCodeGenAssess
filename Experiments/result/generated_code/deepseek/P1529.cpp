#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 52
#define INF INT_MAX

int minDistance(int dist[], int visited[], int n) {
    int min = INF, min_index;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[MAX_NODES][MAX_NODES], int src, int n, int dist[]) {
    int visited[MAX_NODES] = {0};
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);
        visited[u] = 1;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main() {
    int P;
    scanf("%d", &P);

    int graph[MAX_NODES][MAX_NODES] = {0};
    for (int i = 0; i < P; i++) {
        char u, v;
        int w;
        scanf(" %c %c %d", &u, &v, &w);
        int u_index = (u >= 'A' && u <= 'Z') ? u - 'A' : u - 'a' + 26;
        int v_index = (v >= 'A' && v <= 'Z') ? v - 'A' : v - 'a' + 26;
        if (graph[u_index][v_index] == 0 || graph[u_index][v_index] > w) {
            graph[u_index][v_index] = w;
            graph[v_index][u_index] = w;
        }
    }

    int dist[MAX_NODES];
    dijkstra(graph, 'Z' - 'A', MAX_NODES, dist);

    int min_dist = INF;
    char min_cow = 'A';
    for (char cow = 'A'; cow <= 'Y'; cow++) {
        int cow_index = cow - 'A';
        if (dist[cow_index] < min_dist) {
            min_dist = dist[cow_index];
            min_cow = cow;
        }
    }

    printf("%c %d\n", min_cow, min_dist);

    return 0;
}