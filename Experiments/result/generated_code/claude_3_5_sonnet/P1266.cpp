#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_N 150
#define MAX_M 22350

typedef struct {
    int from, to, speed, length;
} Road;

Road roads[MAX_M];
int n, m, d;
double dist[MAX_N];
int prev[MAX_N];
int visited[MAX_N];

void dijkstra() {
    for (int i = 0; i < n; i++) {
        dist[i] = DBL_MAX;
        prev[i] = -1;
        visited[i] = 0;
    }
    
    dist[0] = 0;
    double speed = 70;
    
    for (int i = 0; i < n; i++) {
        int u = -1;
        double min_dist = DBL_MAX;
        
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        
        if (u == -1) break;
        visited[u] = 1;
        
        for (int j = 0; j < m; j++) {
            if (roads[j].from == u) {
                int v = roads[j].to;
                double new_speed = roads[j].speed == 0 ? speed : roads[j].speed;
                double time = (double)roads[j].length / new_speed;
                
                if (dist[u] + time < dist[v]) {
                    dist[v] = dist[u] + time;
                    prev[v] = u;
                    if (roads[j].speed != 0) speed = roads[j].speed;
                }
            }
        }
    }
}

void print_path(int node) {
    if (prev[node] != -1) {
        print_path(prev[node]);
    }
    printf("%d ", node);
}

int main() {
    scanf("%d %d %d", &n, &m, &d);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &roads[i].from, &roads[i].to, &roads[i].speed, &roads[i].length);
    }
    
    dijkstra();
    print_path(d);
    printf("\n");
    
    return 0;
}