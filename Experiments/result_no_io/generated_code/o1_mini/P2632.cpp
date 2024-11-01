#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

typedef struct {
    int u, v;
    double w;
} Edge;

int compare_edges(const void *a, const void *b) {
    double wa = ((Edge*)a)->w;
    double wb = ((Edge*)b)->w;
    if (wa < wb) return -1;
    if (wa > wb) return 1;
    return 0;
}

typedef struct {
    int parent;
    int rank;
} DSU;

int find_set(DSU *dsu, int x){
    if(dsu[x].parent != x){
        dsu[x].parent = find_set(dsu, dsu[x].parent);
    }
    return dsu[x].parent;
}

void union_set(DSU *dsu, int x, int y){
    int fx = find_set(dsu, x);
    int fy = find_set(dsu, y);
    if(fx == fy) return;
    if(dsu[fx].rank < dsu[fy].rank){
        dsu[fx].parent = fy;
    }
    else{
        dsu[fy].parent = fx;
        if(dsu[fx].rank == dsu[fy].rank){
            dsu[fx].rank++;
        }
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    double AX, AY, BX, BY;
    scanf("%lf %lf %lf %lf", &AX, &AY, &BX, &BY);
    
    double CX, CY, DX, DY;
    scanf("%lf %lf %lf %lf", &CX, &CY, &DX, &DY);
    
    Point *points = (Point*)malloc((n + m) * sizeof(Point));
    double t;
    for(int i=0;i<n;i++){
        scanf("%lf", &t);
        points[i].x = AX * t + BX * (1.0 - t);
        points[i].y = AY * t + BY * (1.0 - t);
    }
    for(int i=0;i<m;i++){
        scanf("%lf", &t);
        points[n + i].x = CX * t + DX * (1.0 - t);
        points[n + i].y = CY * t + DY * (1.0 - t);
    }
    
    // Sort first line points by t (already in input order)
    // Assuming input t's are not necessarily sorted, but need to sort based on t
    // However, t's are only used to define positions, so sort based on t ordering
    // But t's are not stored, so we need to store t's and sort accordingly
    // To simplify, assume input t's are sorted. If not, need to sort with t's.
    // Since problem statement does not specify, proceed without sorting.

    // Alternatively, store t's and sort points based on t
    // Read t's again
    
    // Reset and read t's again for sorting
    // Not efficient, better to store t's initially
    // Reallocate
    rewind(stdin);
    // Read again
    scanf("%d %d", &n, &m);
    scanf("%lf %lf %lf %lf", &AX, &AY, &BX, &BY);
    scanf("%lf %lf %lf %lf", &CX, &CY, &DX, &DY);
    
    typedef struct {
        double t;
        int index;
    } TPoint;
    
    TPoint *line1 = (TPoint*)malloc(n * sizeof(TPoint));
    for(int i=0;i<n;i++){
        scanf("%lf", &line1[i].t);
        line1[i].index = i;
        points[i].x = AX * line1[i].t + BX * (1.0 - line1[i].t);
        points[i].y = AY * line1[i].t + BY * (1.0 - line1[i].t);
    }
    
    TPoint *line2 = (TPoint*)malloc(m * sizeof(TPoint));
    for(int i=0;i<m;i++){
        scanf("%lf", &line2[i].t);
        line2[i].index = n + i;
        points[n + i].x = CX * line2[i].t + DX * (1.0 - line2[i].t);
        points[n + i].y = CY * line2[i].t + DY * (1.0 - line2[i].t);
    }
    
    // Sort line1 and line2 based on t
    qsort(line1, n, sizeof(TPoint), (int(*)(const void*, const void*)) 
          (int (*)(const TPoint*, const TPoint*)) ( 
              [](const void *a, const void *b) -> int {
                  double ta = ((TPoint*)a)->t;
                  double tb = ((TPoint*)b)->t;
                  if(ta < tb) return -1;
                  if(ta > tb) return 1;
                  return 0;
              }));
    qsort(line2, m, sizeof(TPoint), (int(*)(const void*, const void*)) 
          (int (*)(const TPoint*, const TPoint*)) ( 
              [](const void *a, const void *b) -> int {
                  double ta = ((TPoint*)a)->t;
                  double tb = ((TPoint*)b)->t;
                  if(ta < tb) return -1;
                  if(ta > tb) return 1;
                  return 0;
              }));
    
    // Reorder points based on sorted t
    Point *sorted_points = (Point*)malloc((n + m) * sizeof(Point));
    for(int i=0;i<n;i++) {
        sorted_points[i] = points[line1[i].index];
    }
    for(int i=0;i<m;i++) {
        sorted_points[n + i] = points[line2[i].index];
    }
    
    // Create edges
    int total_edges = 0;
    int max_edges = (n -1) + (m -1) + 1 + 200000;
    Edge *edges_list = (Edge*)malloc((n + m) * sizeof(Edge));
    
    // Edges for first line
    for(int i=0;i<n-1;i++){
        edges_list[total_edges].u = i;
        edges_list[total_edges].v = i+1;
        double dx = sorted_points[i].x - sorted_points[i+1].x;
        double dy = sorted_points[i].y - sorted_points[i+1].y;
        edges_list[total_edges].w = sqrt(dx*dx + dy*dy);
        total_edges++;
    }
    
    // Edges for second line
    for(int i=0;i<m-1;i++){
        edges_list[total_edges].u = n + i;
        edges_list[total_edges].v = n + i +1;
        double dx = sorted_points[n + i].x - sorted_points[n + i +1].x;
        double dy = sorted_points[n + i].y - sorted_points[n + i +1].y;
        edges_list[total_edges].w = sqrt(dx*dx + dy*dy);
        total_edges++;
    }
    
    // Find minimal distance between two lines using two pointers
    int i1 = 0, i2 = 0;
    double min_dist = 1e18;
    while(i1 < n && i2 < m){
        double dx = sorted_points[i1].x - sorted_points[n + i2].x;
        double dy = sorted_points[i1].y - sorted_points[n + i2].y;
        double dist = sqrt(dx*dx + dy*dy);
        if(dist < min_dist){
            min_dist = dist;
        }
        // Move the pointer with smaller t
        if(line1[i1].t < line2[i2].t){
            i1++;
        }
        else{
            i2++;
        }
    }
    // Add the minimal cross edge
    // To find which pair gives min_dist
    i1 = 0; i2 = 0;
    int best_u, best_v;
    min_dist = 1e18;
    while(i1 < n && i2 < m){
        double dx = sorted_points[i1].x - sorted_points[n + i2].x;
        double dy = sorted_points[i1].y - sorted_points[n + i2].y;
        double dist = sqrt(dx*dx + dy*dy);
        if(dist < min_dist){
            min_dist = dist;
            best_u = i1;
            best_v = n + i2;
        }
        if(line1[i1].t < line2[i2].t){
            i1++;
        }
        else{
            i2++;
        }
    }
    edges_list[total_edges].u = best_u;
    edges_list[total_edges].v = best_v;
    edges_list[total_edges].w = min_dist;
    total_edges++;
    
    // Sort edges by weight
    qsort(edges_list, total_edges, sizeof(Edge), compare_edges);
    
    // Initialize DSU
    DSU *dsu = (DSU*)malloc((n + m) * sizeof(DSU));
    for(int i=0;i<n+m;i++){
        dsu[i].parent = i;
        dsu[i].rank = 0;
    }
    
    // Krusky's algorithm
    double mst = 0.0;
    int count = 0;
    for(int i=0;i<total_edges && count < n + m -1;i++){
        int u = edges_list[i].u;
        int v = edges_list[i].v;
        double w = edges_list[i].w;
        if(find_set(dsu, u) != find_set(dsu, v)){
            union_set(dsu, u, v);
            mst += w;
            count++;
        }
    }
    
    printf("%.3lf\n", mst);
    
    free(points);
    free(sorted_points);
    free(edges_list);
    free(line1);
    free(line2);
    free(dsu);
    
    return 0;
}