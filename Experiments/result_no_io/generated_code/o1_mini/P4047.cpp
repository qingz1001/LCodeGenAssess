#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int u;
    int v;
    double d;
} Edge;

int cmp(const void *a, const void *b) {
    double diff = ((Edge*)a)->d - ((Edge*)b)->d;
    if (diff < 0) return -1;
    else if (diff > 0) return 1;
    else return 0;
}

int parent[1000];
int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int x[n], y[n];
    for(int i=0;i<n;i++) scanf("%d %d", &x[i], &y[i]);
    int m = n*(n-1)/2;
    Edge *edges = (Edge*)malloc(sizeof(Edge)*m);
    int idx =0;
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            edges[idx].u = i;
            edges[idx].v = j;
            edges[idx].d = sqrt(dx*dx + dy*dy);
            idx++;
        }
    }
    qsort(edges, m, sizeof(Edge), cmp);
    for(int i=0;i<n;i++) parent[i]=i;
    int cluster = n;
    double answer = 0.0;
    for(int i=0;i<m;i++) {
        int fu = find_set(edges[i].u);
        int fv = find_set(edges[i].v);
        if(fu != fv){
            if(cluster > k){
                parent[fu] = fv;
                cluster--;
            }
            else{
                answer = edges[i].d;
                break;
            }
        }
    }
    printf("%.2lf\n", answer);
    free(edges);
    return 0;
}