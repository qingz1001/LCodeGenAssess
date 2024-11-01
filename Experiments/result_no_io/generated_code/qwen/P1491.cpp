#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 205
#define INF 99999999

typedef struct {
    int to, dist;
} Edge;

int n, m;
double x[MAXN], y[MAXN];
Edge edges[10005];
int degree[MAXN];

void add_edge(int from, int to, double dist) {
    edges[m].to = to;
    edges[m].dist = (int)(dist * 100 + 0.5);
    m++;
}

double distance(int i, int j) {
    return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

int dijkstra(int start, int end, int exclude) {
    int dist[MAXN];
    int visited[MAXN];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[start] = 0;
    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }
        visited[u] = 1;
        for (int j = 0; j < degree[u]; j++) {
            int v = edges[edges[u][j]].to;
            int d = edges[edges[u][j]].dist;
            if (v != exclude && dist[u] + d < dist[v]) {
                dist[v] = dist[u] + d;
            }
        }
    }
    return dist[end];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &x[i], &y[i]);
    }
    for (int i = 0; i < m; i++) {
        int p, q;
        scanf("%d %d", &p, &q);
        double dist = distance(p - 1, q - 1);
        add_edge(p - 1, q - 1, dist);
        add_edge(q - 1, p - 1, dist);
        degree[p - 1]++;
        degree[q - 1]++;
    }

    int first_shortest = dijkstra(0, n - 1, -1);
    if (first_shortest == INF) {
        printf("-1\n");
        return 0;
    }

    int second_shortest = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < degree[i]; j++) {
            int v = edges[edges[i][j]].to;
            int d = edges[edges[i][j]].dist;
            int alt = dijkstra(0, n - 1, v);
            if (alt != INF && alt > first_shortest && alt < second_shortest) {
                second_shortest = alt;
            }
        }
    }

    printf("%.2f\n", second_shortest / 100.0);
    return 0;
}