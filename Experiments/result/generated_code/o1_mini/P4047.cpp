#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    double distance;
    int u;
    int v;
} Edge;

int cmp(const void *a, const void *b) {
    double diff = ((Edge*)a)->distance - ((Edge*)b)->distance;
    if (diff < 0) return -1;
    else if (diff > 0) return 1;
    else return 0;
}

int parent[1001];
int rank_set[1001];

int find_set_func(int x){
    if(parent[x] != x){
        parent[x] = find_set_func(parent[x]);
    }
    return parent[x];
}

void union_set_func(int x, int y){
    int fx = find_set_func(x);
    int fy = find_set_func(y);
    if(fx == fy) return;
    if(rank_set[fx] < rank_set[fy]){
        parent[fx] = fy;
    }
    else{
        parent[fy] = fx;
        if(rank_set[fx] == rank_set[fy]){
            rank_set[fx]++;
        }
    }
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    Point points[1001];
    for(int i=0; i<n; i++) scanf("%d %d", &points[i].x, &points[i].y);
    int m = n*(n-1)/2;
    Edge *edges = (Edge*)malloc(sizeof(Edge)*m);
    int idx = 0;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            double dx = (double)(points[i].x - points[j].x);
            double dy = (double)(points[i].y - points[j].y);
            edges[idx].distance = sqrt(dx*dx + dy*dy);
            edges[idx].u = i;
            edges[idx].v = j;
            idx++;
        }
    }
    qsort(edges, m, sizeof(Edge), cmp);
    for(int i=0; i<n; i++) { parent[i] = i; rank_set[i] = 0; }
    int cluster_count = n;
    double result = 0.0;
    for(int i=0; i<m; i++){
        int u = edges[i].u;
        int v = edges[i].v;
        int fu = find_set_func(u);
        int fv = find_set_func(v);
        if(fu != fv){
            if(cluster_count > k){
                union_set_func(fu, fv);
                cluster_count--;
            }
            else{
                result = edges[i].distance;
                break;
            }
        }
    }
    printf("%.2lf\n", result);
    free(edges);
    return 0;
}