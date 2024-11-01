#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_N 100
#define MAX_M 1000

typedef struct {
    int x, y;
} Point;

Point stores[MAX_N + 1];
int graph[MAX_N + 1][MAX_N + 1];
double dist[MAX_N + 1];
int visited[MAX_N + 1];

double calculate_distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int find_min_dist(int n) {
    double min_dist = DBL_MAX;
    int min_index = -1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && dist[i] < min_dist) {
            min_dist = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

double dijkstra(int n, int s, int t) {
    for (int i = 1; i <= n; i++) {
        dist[i] = DBL_MAX;
        visited[i] = 0;
    }
    
    dist[s] = 0;
    
    for (int count = 0; count < n - 1; count++) {
        int u = find_min_dist(n);
        visited[u] = 1;
        
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    
    return dist[t];
}

int main() {
    int n, m, s, t;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &stores[i].x, &stores[i].y);
    }
    
    scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        double distance = calculate_distance(stores[a], stores[b]);
        graph[a][b] = graph[b][a] = distance;
    }
    
    scanf("%d %d", &s, &t);
    
    double shortest_distance = dijkstra(n, s, t);
    
    printf("%.2f\n", shortest_distance);
    
    return 0;
}