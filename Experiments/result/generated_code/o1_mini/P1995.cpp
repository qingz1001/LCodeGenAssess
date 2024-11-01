#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_NODES 5000
#define MAX_RECT 100
#define INF 1e18

typedef struct {
    double x, y;
} Point;

typedef struct {
    int from;
    int to;
    double cost;
} Edge;

int n;
int rect_count = 0;
double x1[MAX_RECT], y1[MAX_RECT], x2[MAX_RECT], y2[MAX_RECT];
Point nodes[MAX_NODES];
int node_count = 0;
Edge edges[MAX_NODES * MAX_NODES];
int edge_count = 0;

int add_node(double x, double y) {
    for(int i=0;i<node_count;i++) {
        if(fabs(nodes[i].x - x) < 1e-8 && fabs(nodes[i].y - y) < 1e-8)
            return i;
    }
    nodes[node_count].x = x;
    nodes[node_count].y = y;
    return node_count++;
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++) {
        scanf("%lf %lf %lf %lf", &x1[i], &y1[i], &x2[i], &y2[i]);
    }
    double sx, sy, tx, ty, v;
    scanf("%lf %lf", &sx, &sy);
    scanf("%lf %lf", &tx, &ty);
    scanf("%lf", &v);
    // Add S and T
    int S = add_node(sx, sy);
    int T = add_node(tx, ty);
    // Add rectangle corners
    for(int i=0;i<n;i++) {
        add_node(x1[i], y1[i]);
        add_node(x1[i], y2[i]);
        add_node(x2[i], y1[i]);
        add_node(x2[i], y2[i]);
    }
    // Function to check if a point is inside any rectangle
    auto point_inside = [&](double x, double y) -> int {
        for(int i=0;i<n;i++) {
            if(x1[i] -1e-8 <= x && x <= x2[i]+1e-8 && y1[i]-1e-8 <= y && y <= y2[i]+1e-8)
                return 1;
        }
        return 0;
    };
    // Function to check if a line segment is inside the union
    // Sample points along the line and check
    auto line_inside = [&](Point a, Point b) -> int {
        if(!point_inside(a.x, a.y) || !point_inside(b.x, b.y))
            return 0;
        int samples = 100;
        for(int i=0;i<=samples;i++) {
            double t = (double)i / samples;
            double x = a.x + (b.x - a.x) * t;
            double y = a.y + (b.y - a.y) * t;
            if(!point_inside(x, y))
                return 0;
        }
        return 1;
    };
    // Build edges
    for(int i=0;i<node_count;i++) {
        for(int j=i+1;j<node_count;j++) {
            Point a = nodes[i];
            Point b = nodes[j];
            if(line_inside(a, b)) {
                double dist = sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
                edges[edge_count].from = i;
                edges[edge_count].to = j;
                edges[edge_count].cost = dist;
                edge_count++;
                edges[edge_count].from = j;
                edges[edge_count].to = i;
                edges[edge_count].cost = dist;
                edge_count++;
            }
        }
    }
    // Dijkstra
    double dist_arr[MAX_NODES];
    for(int i=0;i<node_count;i++) dist_arr[i] = INF;
    dist_arr[S] = 0.0;
    int visited[MAX_NODES] = {0};
    for(int i=0;i<node_count;i++) {
        double min_dist = INF;
        int u = -1;
        for(int j=0;j<node_count;j++) {
            if(!visited[j] && dist_arr[j] < min_dist) {
                min_dist = dist_arr[j];
                u = j;
            }
        }
        if(u == -1) break;
        if(u == T) break;
        visited[u] = 1;
        for(int e=0;e<edge_count;e++) {
            if(edges[e].from == u) {
                int v_idx = edges[e].to;
                if(!visited[v_idx] && dist_arr[u] + edges[e].cost < dist_arr[v_idx]) {
                    dist_arr[v_idx] = dist_arr[u] + edges[e].cost;
                }
            }
        }
    }
    double time = dist_arr[T] / v;
    printf("%.10lf\n", time);
}