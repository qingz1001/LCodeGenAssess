#include <stdio.h>
#include <limits.h>

#define MAX_VILLAGES 20

int min(int a, int b) {
    return (a < b) ? a : b;
}

void floydWarshall(int graph[MAX_VILLAGES][MAX_VILLAGES], int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][k] != INT_MAX && graph[k][j] != INT_MAX &&
                    graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int graph[MAX_VILLAGES][MAX_VILLAGES];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = INT_MAX;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    floydWarshall(graph, n);

    int shortestPath = INT_MAX;

    for (int i = 0; i < n; i++) {
        shortestPath = min(shortestPath, graph[0][i] + graph[i][0]);
    }

    printf("%d\n", shortestPath);

    return 0;
}