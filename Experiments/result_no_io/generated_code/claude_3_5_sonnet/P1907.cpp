#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_N 1000

typedef struct {
    double x, y;
} Point;

Point intersections[MAX_N];
int rome_road[MAX_N][MAX_N] = {0};
int n;
double dirt_cost, rome_cost;

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double dijkstra(Point start, Point end) {
    double dist_to[MAX_N];
    int visited[MAX_N] = {0};
    
    for (int i = 0; i < n; i++) {
        dist_to[i] = DBL_MAX;
    }
    
    dist_to[0] = 0;
    
    for (int i = 0; i < n; i++) {
        int u = -1;
        double min_dist = DBL_MAX;
        
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist_to[j] < min_dist) {
                u = j;
                min_dist = dist_to[j];
            }
        }
        
        if (u == -1) break;
        visited[u] = 1;
        
        for (int v = 0; v < n; v++) {
            if (visited[v]) continue;
            double d = dist(intersections[u], intersections[v]);
            double cost = rome_road[u][v] ? rome_cost * d : dirt_cost * d;
            if (dist_to[u] + cost < dist_to[v]) {
                dist_to[v] = dist_to[u] + cost;
            }
        }
    }
    
    double start_cost = DBL_MAX, end_cost = DBL_MAX;
    for (int i = 0; i < n; i++) {
        double d1 = dist(start, intersections[i]);
        double d2 = dist(end, intersections[i]);
        start_cost = fmin(start_cost, dist_to[i] + dirt_cost * d1);
        end_cost = fmin(end_cost, dist_to[i] + dirt_cost * d2);
    }
    
    return start_cost + end_cost;
}

int main() {
    scanf("%lf %lf", &dirt_cost, &rome_cost);
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &intersections[i].x, &intersections[i].y);
    }
    
    int i, j;
    while (scanf("%d %d", &i, &j) && (i != 0 || j != 0)) {
        rome_road[i-1][j-1] = rome_road[j-1][i-1] = 1;
    }
    
    Point dock, home;
    scanf("%lf %lf", &dock.x, &dock.y);
    scanf("%lf %lf", &home.x, &home.y);
    
    double result = dijkstra(dock, home);
    printf("%.4f\n", result);
    
    return 0;
}