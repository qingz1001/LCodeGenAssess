#include <stdio.h>
#include <limits.h>

#define MAX_VILLAGES 20

int min(int a, int b) {
    return a < b ? a : b;
}

void tsp(int graph[MAX_VILLAGES][MAX_VILLAGES], int n, int start) {
    int visited[MAX_VILLAGES] = {0};
    visited[start] = 1;

    int path[MAX_VILLAGES];
    path[0] = start;
    int count = 1;

    int min_path = INT_MAX;

    for (int i = 0; i < n - 1; i++) {
        int min_cost = INT_MAX;
        int next Village = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[path[count - 1]][j] != 0 && graph[path[count - 1]][j] < min_cost) {
                min_cost = graph[path[count - 1]][j];
                nextVillage = j;
            }
        }

        visited[nextVillage] = 1;
        path[count++] = nextVillage;
        min_path += min_cost;
    }

    min_path += graph[path[count - 1]][start];

    printf("%d\n", min_path);
}

int main() {
    int n;
    scanf("%d", &n);

    int graph[MAX_VILLAGES][MAX_VILLAGES];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    tsp(graph, n, 0);

    return 0;
}