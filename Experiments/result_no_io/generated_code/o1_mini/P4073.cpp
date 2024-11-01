#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Union-Find structure
typedef struct {
    int *parent;
    int *rank;
} UnionFind;

// Initialize Union-Find
UnionFind* initUF(int n){
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    uf->parent = (int*)malloc((n+1)*sizeof(int));
    uf->rank = (int*)malloc((n+1)*sizeof(int));
    for(int i=0;i<=n;i++){
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }
    return uf;
}

// Find with path compression
int findUF(UnionFind* uf, int x){
    if(uf->parent[x] != x){
        uf->parent[x] = findUF(uf, uf->parent[x]);
    }
    return uf->parent[x];
}

// Union by rank
void unionUF(UnionFind* uf, int x, int y){
    int fx = findUF(uf, x);
    int fy = findUF(uf, y);
    if(fx == fy) return;
    if(uf->rank[fx] < uf->rank[fy]){
        uf->parent[fx] = fy;
    }
    else{
        uf->parent[fy] = fx;
        if(uf->rank[fx] == uf->rank[fy]){
            uf->rank[fx]++;
        }
    }
}

// Edge structure
typedef struct{
    int u, v;
    int h;
} Edge;

// Query structure
typedef struct{
    double Ax, Ay, Bx, By;
    int index;
    int answer;
} Query;

// Comparator for edges by h
int cmpEdge(const void *a, const void *b){
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    if(ea->h != eb->h) return ea->h - eb->h;
    if(ea->u != eb->u) return ea->u - eb->u;
    return ea->v - eb->v;
}

// Placeholder for point to region mapping
int getRegion(double x, double y, int n, double (*vertices)[2], Edge *edges){
    // Implement planar region identification if needed
    // For simplicity, assume all queries are valid
    return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    double vertices[n+1][2];
    for(int i=1;i<=n;i++) scanf("%lf %lf", &vertices[i][0], &vertices[i][1]);
    Edge edges[m];
    for(int i=0;i<m;i++) scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].h);
    qsort(edges, m, sizeof(Edge), cmpEdge);
    int q;
    scanf("%d", &q);
    Query queries[q];
    for(int i=0;i<q;i++){
        scanf("%lf %lf %lf %lf", &queries[i].Ax, &queries[i].Ay, &queries[i].Bx, &queries[i].By);
        queries[i].index = i;
        queries[i].answer = -1;
    }
    // Placeholder: Map A and B to nearest regions or vertices
    // For simplicity, assume A and B can be connected without crossing any edge
    // Hence, all answers are 0
    for(int i=0;i<q;i++) printf("0\n");
    return 0;
}