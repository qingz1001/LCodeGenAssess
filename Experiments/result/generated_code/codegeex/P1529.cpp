#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 200

int dist[MAXN];
int graph[MAXN][MAXN];
int visited[MAXN];
int n;

void dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        int min_dist = INT_MAX;
        int min_vertex = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                min_vertex = j;
            }
        }

        if (min_vertex == -1) break;

        visited[min_vertex] = 1;

        for (int j = 0; j < n; j++) {
            if (graph[min_vertex][j] != INT_MAX && dist[min_vertex] + graph[min_vertex][j] < dist[j]) {
                dist[j] = dist[min_vertex] + graph[min_vertex][j];
            }
        }
    }
}

int main() {
    int m;
    scanf("%d", &m);
    n = 0;
    char a, b;
    int c;

    for (int i = 0; i < m; i++) {
        scanf(" %c %c %d", &a, &b, &c);
        int u = a - 'A';
        int v = b - 'A';

        if (u >= 0 && u < 26) {
            if (n <= u) n = u + 1;
        }
        if (v >= 0 && v < 26) {
            if (n <= v) n = v + 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < m; i++) {
        scanf(" %c %c %d", &a, &b, &c);
        int u = a - 'A';
        int v = b - 'A';

        if (u >= 0 && u < 26 && v >= 0 && v < 26) {
            if (graph[u][v] > c) {
                graph[u][v] = c;
                graph[v][u] = c;
            }
        }
    }

    dijkstra(25); // 'Z' - 'A' = 25

    int min_dist = INT_MAX;
    char min_cow = 'A';

    for (int i = 0; i < 26; i++) {
        if ('A' + i != 'Z' && dist[i] < min_dist) {
            min_dist = dist[i];
            min_cow = 'A' + i;
        }
    }

    printf("%c %d\n", min_cow, min_dist);

    return 0;
}