#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_N 200
#define MAX_M 10000
#define INF DBL_MAX

typedef struct {
    int x, y;
} Point;

typedef struct {
    int u, v;
    double w;
} Edge;

Point points[MAX_N];
Edge edges[MAX_M];
double dist[MAX_N];
int prev[MAX_N];
int n, m;

double calculate_distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void dijkstra(int start) {
    int visited[MAX_N] = {0};
    
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    
    dist[start] = 0;
    
    for (int i = 0; i < n; i++) {
        int u = -1;
        double min_dist = INF;
        
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        
        if (u == -1) break;
        
        visited[u] = 1;
        
        for (int j = 0; j < m; j++) {
            if (edges[j].u == u + 1) {
                int v = edges[j].v - 1;
                double alt = dist[u] + edges[j].w;
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                }
            }
        }
    }
}

double find_second_shortest_path() {
    double shortest = dist[n-1];
    double second_shortest = INF;
    
    for (int i = 0; i < m; i++) {
        int u = edges[i].u - 1;
        int v = edges[i].v - 1;
        double original_weight = edges[i].w;
        
        edges[i].w = INF;
        
        dijkstra(0);
        
        if (dist[n-1] > shortest && dist[n-1] < second_shortest) {
            second_shortest = dist[n-1];
        }
        
        edges[i].w = original_weight;
    }
    
    return second_shortest;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
        edges[i].w = calculate_distance(points[edges[i].u-1], points[edges[i].v-1]);
    }
    
    dijkstra(0);
    double shortest_path = dist[n-1];
    
    double second_shortest_path = find_second_shortest_path();
    
    if (second_shortest_path == INF) {
        printf("-1\n");
    } else {
        printf("%.2f\n", second_shortest_path);
    }
    
    return 0;
}