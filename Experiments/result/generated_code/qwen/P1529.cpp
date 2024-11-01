#include <stdio.h>
#include <stdlib.h>

#define MAX_PASTURES 27
#define INF 1000000

typedef struct {
    int distance;
    char predecessor;
} Node;

int main() {
    int P, i, j, k;
    char start, end;
    int length;
    Node graph[MAX_PASTURES][MAX_PASTURES];
    char pastures[MAX_PASTURES];
    int n = 0;

    // Initialize the graph and pastures array
    for (i = 0; i < MAX_PASTURES; i++) {
        for (j = 0; j < MAX_PASTURES; j++) {
            if (i == j) {
                graph[i][j].distance = 0;
                graph[i][j].predecessor = '\0';
            } else {
                graph[i][j].distance = INF;
                graph[i][j].predecessor = '\0';
            }
        }
        pastures[i] = '\0';
    }

    // Read input
    scanf("%d", &P);
    for (i = 0; i < P; i++) {
        scanf(" %c %c %d", &start, &end, &length);
        int idx_start = start >= 'a' ? start - 'a' : start - 'A' + 26;
        int idx_end = end >= 'a' ? end - 'a' : end - 'A' + 26;
        graph[idx_start][idx_end].distance = length;
        graph[idx_end][idx_start].distance = length;
    }

    // Find the starting pasture with a cow
    for (i = 0; i < MAX_PASTURES; i++) {
        if (pastures[i] != '\0') {
            start = pastures[i];
            break;
        }
    }

    // Dijkstra's algorithm to find the shortest path to the barn
    int dist[MAX_PASTURES];
    char pred[MAX_PASTURES];
    for (i = 0; i < MAX_PASTURES; i++) {
        dist[i] = graph[start - 'a'][i].distance;
        pred[i] = start;
    }
    dist[start - 'a'] = 0;
    pred[start - 'a'] = '\0';

    for (k = 0; k < MAX_PASTURES; k++) {
        int u = -1;
        for (i = 0; i < MAX_PASTURES; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        visited[u] = 1;
        for (v = 0; v < MAX_PASTURES; v++) {
            if (!visited[v] && dist[u] + graph[u][v].distance < dist[v]) {
                dist[v] = dist[u] + graph[u][v].distance;
                pred[v] = u;
            }
        }
    }

    // Output the result
    printf("%c %d\n", start, dist[end - 'a']);

    return 0;
}