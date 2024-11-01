#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_NODES 82
#define INF 1e18

typedef struct {
    double x, y;
} Point;

typedef struct {
    double dist;
    bool visited;
} DNode;

int n;
double walls_x[20];
double walls_a1[20], walls_b1[20], walls_a2[20], walls_b2[20];
Point nodes[MAX_NODES];
int node_count = 0;
double adj[MAX_NODES][MAX_NODES];

bool can_see(Point a, Point b) {
    if (a.x == b.x && a.y == b.y) return true;
    for(int i=0;i<n;i++) {
        double xi = walls_x[i];
        if ((a.x < xi && b.x < xi) || (a.x > xi && b.x > xi)) continue;
        double t = (xi - a.x) / (b.x - a.x);
        if (t < 0 || t > 1) continue;
        double y = a.y + t*(b.y - a.y);
        if (!((walls_a1[i] <= y && y <= walls_b1[i]) || (walls_a2[i] <= y && y <= walls_b2[i]))) {
            return false;
        }
    }
    return true;
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++) {
        scanf("%lf %lf %lf %lf %lf", &walls_x[i], &walls_a1[i], &walls_b1[i], &walls_a2[i], &walls_b2[i]);
    }
    // Add entrance
    nodes[node_count].x = 0.0;
    nodes[node_count].y = 5.0;
    node_count++;
    // Add exit
    nodes[node_count].x = 10.0;
    nodes[node_count].y = 5.0;
    node_count++;
    // Add gap points
    for(int i=0;i<n;i++) {
        nodes[node_count].x = walls_x[i];
        nodes[node_count].y = walls_a1[i];
        node_count++;
        nodes[node_count].x = walls_x[i];
        nodes[node_count].y = walls_b1[i];
        node_count++;
        nodes[node_count].x = walls_x[i];
        nodes[node_count].y = walls_a2[i];
        node_count++;
        nodes[node_count].x = walls_x[i];
        nodes[node_count].y = walls_b2[i];
        node_count++;
    }
    // Initialize adjacency
    for(int i=0;i<node_count;i++) {
        for(int j=0;j<node_count;j++) {
            if(i == j){
                adj[i][j] = 0.0;
            }
            else{
                if(can_see(nodes[i], nodes[j])){
                    double dx = nodes[i].x - nodes[j].x;
                    double dy = nodes[i].y - nodes[j].y;
                    adj[i][j] = sqrt(dx*dx + dy*dy);
                }
                else{
                    adj[i][j] = INF;
                }
            }
        }
    }
    // Dijkstra
    DNode d[MAX_NODES];
    for(int i=0;i<node_count;i++) {
        d[i].dist = INF;
        d[i].visited = false;
    }
    d[0].dist = 0.0;
    for(int i=0;i<node_count;i++) {
        // Find min
        double min_dist = INF;
        int u = -1;
        for(int j=0;j<node_count;j++) {
            if(!d[j].visited && d[j].dist < min_dist){
                min_dist = d[j].dist;
                u = j;
            }
        }
        if(u == -1) break;
        d[u].visited = true;
        for(int v=0;v<node_count;v++) {
            if(!d[v].visited && adj[u][v] < INF){
                if(d[u].dist + adj[u][v] < d[v].dist){
                    d[v].dist = d[u].dist + adj[u][v];
                }
            }
        }
    }
    printf("%.2lf\n", d[1]);
    return 0;
}