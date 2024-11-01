#include <stdio.h>
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
        char a, b;
        int d;
        scanf(" %c %c %d", &a, &b, &d);
        int u = (a >= 'A' && a <= 'Z') ? a - 'A' : a - 'a' + 26;
        int v = (b >= 'A' && b <= 'Z') ? b - 'A' : b - 'a' + 26;
        if (graph[u][v] == 0 || graph[u][v] > d) {
            graph[u][v] = d;
            graph[v][u] = d;
        }
    }

    int dist[MAX_NODES];
    dijkstra(graph, 'Z' - 'A', MAX_NODES, dist);

    int min_cow_dist = INF;
    char min_cow_id = 'A';
    for (char c = 'A'; c <= 'Y'; c++) {
        int idx = c - 'A';
        if (dist[idx] < min_cow_dist) {
            min_cow_dist = dist[idx];
            min_cow_id = c;
        }
    }

    printf("%c %d\n", min_cow_id, min_cow_dist);

    return 0;
}