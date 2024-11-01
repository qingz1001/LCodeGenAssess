#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX_POINTS 82
#define INF 1e18

typedef struct {
    double x, y;
} Point;

int main(){
    int n;
    scanf("%d", &n);
    
    double wall_x[20];
    double a1[20], b1[20], a2[20], b2[20];
    for(int i=0;i<n;i++) {
        scanf("%lf %lf %lf %lf %lf", &wall_x[i], &a1[i], &b1[i], &a2[i], &b2[i]);
    }
    
    Point points[MAX_POINTS];
    int idx=0;
    // Start and end points
    points[idx].x = 0.0; points[idx].y = 5.0; idx++;
    points[idx].x = 10.0; points[idx].y = 5.0; idx++;
    
    // Openings
    for(int i=0;i<n;i++) {
        points[idx].x = wall_x[i];
        points[idx].y = a1[i]; idx++;
        points[idx].x = wall_x[i];
        points[idx].y = b1[i]; idx++;
        points[idx].x = wall_x[i];
        points[idx].y = a2[i]; idx++;
        points[idx].y = b2[i]; idx++;
    }
    
    int total = idx;
    double adj[MAX_POINTS][MAX_POINTS];
    for(int i=0;i<total;i++) {
        for(int j=0;j<total;j++) {
            if(i == j){
                adj[i][j] = 0.0;
                continue;
            }
            // Check visibility between points[i] and points[j]
            bool visible = true;
            for(int k=0;k<n;k++) {
                double wx = wall_x[k];
                // If both points are on the same side of the wall, no crossing
                if( (points[i].x < wx && points[j].x < wx) || (points[i].x > wx && points[j].x > wx))
                    continue;
                // If one point is exactly on the wall, skip this wall
                if(points[i].x == wx || points[j].x == wx)
                    continue;
                // Find y at x=wx
                double t = (wx - points[i].x) / (points[j].x - points[i].x);
                if(t < 0 || t > 1){
                    continue;
                }
                double y = points[i].y + t * (points[j].y - points[i].y);
                // Check if y is within any gap
                bool in_gap = false;
                if( (y >= a1[k] && y <= b1[k]) || (y >= a2[k] && y <= b2[k]) ){
                    in_gap = true;
                }
                if(!in_gap){
                    visible = false;
                    break;
                }
            }
            if(visible){
                double dx = points[i].x - points[j].x;
                double dy = points[i].y - points[j].y;
                adj[i][j] = sqrt(dx*dx + dy*dy);
            }
            else{
                adj[i][j] = INF;
            }
        }
    }
    
    // Dijkstra
    double dist[MAX_POINTS];
    bool visited_arr[MAX_POINTS];
    for(int i=0;i<total;i++) {
        dist[i] = INF;
        visited_arr[i] = false;
    }
    dist[0] = 0.0;
    
    for(int i=0;i<total;i++) {
        // Find the unvisited node with smallest distance
        double min_dist = INF;
        int u = -1;
        for(int j=0;j<total;j++) {
            if(!visited_arr[j] && dist[j] < min_dist){
                min_dist = dist[j];
                u = j;
            }
        }
        if(u == -1) break;
        visited_arr[u] = true;
        // Update distances
        for(int v=0;v<total;v++) {
            if(!visited_arr[v] && adj[u][v] < INF){
                if(dist[u] + adj[u][v] < dist[v]){
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }
    
    printf("%.2lf\n", dist[1]);
    return 0;
}