#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double t;
    double x, y;
    int index;
} Point;

typedef struct {
    int u, v;
    double dist;
} Edge;

int cmp_points(const void *a, const void *b){
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    if(pa->t < pb->t) return -1;
    if(pa->t > pb->t) return 1;
    return 0;
}

int cmp_edges(const void *a, const void *b){
    Edge *ea = (Edge *)a;
    Edge *eb = (Edge *)b;
    if(ea->dist < eb->dist) return -1;
    if(ea->dist > eb->dist) return 1;
    return 0;
}

int find_set(int *parent, int x){
    if(parent[x] != x){
        parent[x] = find_set(parent, parent[x]);
    }
    return parent[x];
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    int AX, AY, BX, BY;
    scanf("%d %d %d %d", &AX, &AY, &BX, &BY);
    
    int CX, CY, DX, DY;
    scanf("%d %d %d %d", &CX, &CY, &DX, &DY);
    
    Point *line1 = (Point *)malloc(n * sizeof(Point));
    Point *line2 = (Point *)malloc(m * sizeof(Point));
    
    for(int i=0;i<n;i++){
        double t;
        scanf("%lf", &t);
        line1[i].t = t;
        line1[i].x = AX * t + BX * (1.0 - t);
        line1[i].y = AY * t + BY * (1.0 - t);
        line1[i].index = i;
    }
    
    for(int i=0;i<m;i++){
        double t;
        scanf("%lf", &t);
        line2[i].t = t;
        line2[i].x = CX * t + DX * (1.0 - t);
        line2[i].y = CY * t + DY * (1.0 - t);
        line2[i].index = n + i;
    }
    
    qsort(line1, n, sizeof(Point), cmp_points);
    qsort(line2, m, sizeof(Point), cmp_points);
    
    // Create edges
    int max_edges = (n-1) + (m-1) + (n + m);
    Edge *edges = (Edge *)malloc(max_edges * sizeof(Edge));
    int edge_count = 0;
    
    // Edges within line1
    for(int i=0;i<n-1;i++){
        double dx = line1[i+1].x - line1[i].x;
        double dy = line1[i+1].y - line1[i].y;
        edges[edge_count].u = line1[i].index;
        edges[edge_count].v = line1[i+1].index;
        edges[edge_count].dist = sqrt(dx*dx + dy*dy);
        edge_count++;
    }
    
    // Edges within line2
    for(int i=0;i<m-1;i++){
        double dx = line2[i+1].x - line2[i].x;
        double dy = line2[i+1].y - line2[i].y;
        edges[edge_count].u = line2[i].index;
        edges[edge_count].v = line2[i+1].index;
        edges[edge_count].dist = sqrt(dx*dx + dy*dy);
        edge_count++;
    }
    
    // Edges between line1 and line2
    int i =0, j=0;
    while(i < n && j < m){
        double dx = line1[i].x - line2[j].x;
        double dy = line1[i].y - line2[j].y;
        double dist = sqrt(dx*dx + dy*dy);
        edges[edge_count].u = line1[i].index;
        edges[edge_count].v = line2[j].index;
        edges[edge_count].dist = dist;
        edge_count++;
        
        if(line1[i].t < line2[j].t){
            i++;
        }
        else{
            j++;
        }
    }
    
    // After one list is exhausted
    while(i < n){
        double dx = line1[i].x - line2[m-1].x;
        double dy = line1[i].y - line2[m-1].y;
        double dist = sqrt(dx*dx + dy*dy);
        edges[edge_count].u = line1[i].index;
        edges[edge_count].v = line2[m-1].index;
        edges[edge_count].dist = dist;
        edge_count++;
        i++;
    }
    
    while(j < m){
        double dx = line1[n-1].x - line2[j].x;
        double dy = line1[n-1].y - line2[j].y;
        double dist = sqrt(dx*dx + dy*dy);
        edges[edge_count].u = line1[n-1].index;
        edges[edge_count].v = line2[j].index;
        edges[edge_count].dist = dist;
        edge_count++;
        j++;
    }
    
    qsort(edges, edge_count, sizeof(Edge), cmp_edges);
    
    int total_points = n + m;
    int *parent = (int *)malloc(total_points * sizeof(int));
    for(int p=0;p<total_points;p++) parent[p] = p;
    
    double mst =0.0;
    for(int e=0;e<edge_count;e++){
        int pu = find_set(parent, edges[e].u);
        int pv = find_set(parent, edges[e].v);
        if(pu != pv){
            parent[pu] = pv;
            mst += edges[e].dist;
        }
    }
    
    printf("%.3lf\n", mst);
    
    free(line1);
    free(line2);
    free(edges);
    free(parent);
    return 0;
}