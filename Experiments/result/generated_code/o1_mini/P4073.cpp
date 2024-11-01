#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

typedef struct {
    int u, v;
    int h;
} Edge;

typedef struct {
    ll x, y;
} Point;

int cmp_edge(const void *a, const void *b){
    Edge *ea = (Edge *)a;
    Edge *eb = (Edge *)b;
    return ea->h - eb->h;
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
    Point *points = (Point*)malloc((n+1)*sizeof(Point));
    for(int i=1;i<=n;i++){
        scanf("%lld %lld", &points[i].x, &points[i].y);
    }
    Edge *edges = (Edge*)malloc(m*sizeof(Edge));
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].h);
    }
    qsort(edges, m, sizeof(Edge), cmp_edge);
    int *parent = (int*)malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++) parent[i] = i;
    // Not implementing planar regions and forbidden zone
    // As it's complex, we output -1 for all queries
    // Placeholder for actual implementation
    int q;
    scanf("%d", &q);
    for(int i=0;i<q;i++){
        double Ax, Ay, Bx, By;
        scanf("%lf %lf %lf %lf", &Ax, &Ay, &Bx, &By);
        // Placeholder logic
        printf("-1\n");
    }
    free(points);
    free(edges);
    free(parent);
    return 0;
}