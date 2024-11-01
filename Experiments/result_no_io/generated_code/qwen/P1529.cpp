#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASTURES 52
#define MAX_ROADS 10000

typedef struct {
    int id;
    int distance;
} Node;

int compare(const void *a, const void *b) {
    return ((Node *)a)->distance - ((Node *)b)->distance;
}

int main() {
    int P;
    scanf("%d", &P);

    int roads[MAX_ROADS][3];
    for (int i = 0; i < P; i++) {
        scanf(" %c %c %d", &roads[i][0], &roads[i][1], &roads[i][2]);
    }

    int graph[MAX_PASTURES][MAX_PASTURES];
    memset(graph, -1, sizeof(graph));

    for (int i = 0; i < P; i++) {
        int u = roads[i][0] >= 'a' ? roads[i][0] - 'a' : roads[i][0] - 'A';
        int v = roads[i][1] >= 'a' ? roads[i][1] - 'a' : roads[i][1] - 'A';
        int w = roads[i][2];
        graph[u][v] = w;
        graph[v][u] = w;
    }

    int dist[MAX_PASTURES];
    int prev[MAX_PASTURES];
    char from[MAX_PASTURES];

    for (int i = 0; i < MAX_PASTURES; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        from[i] = '\0';
    }

    char start = 'Z' - 'A';
    dist[start] = 0;

    for (int i = 0; i < MAX_PASTURES; i++) {
        int min_dist = INT_MAX;
        int min_index = -1;
        for (int j = 0; j < MAX_PASTURES; j++) {
            if (dist[j] != INT_MAX && (min_index == -1 || dist[j] < min_dist)) {
                min_dist = dist[j];
                min_index = j;
            }
        }

        if (min_index == -1) break;

        for (int j = 0; j < MAX_PASTURES; j++) {
            if (graph[min_index][j] != -1 && dist[min_index] + graph[min_index][j] < dist[j]) {
                dist[j] = dist[min_index] + graph[min_index][j];
                prev[j] = min_index;
                from[j] = from[min_index];
            }
        }
    }

    int end = 'a' - 'A';
    Node nodes[MAX_PASTURES];
    int count = 0;

    while (end != -1) {
        nodes[count].id = end;
        nodes[count].distance = dist[end];
        count++;
        end = prev[end];
    }

    qsort(nodes, count, sizeof(Node), compare);

    printf("%c %d\n", nodes[0].id + 'A', nodes[0].distance);

    return 0;
}