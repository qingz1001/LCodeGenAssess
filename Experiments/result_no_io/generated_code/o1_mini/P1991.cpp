#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int u;
    int v;
    double w;
} Edge;

int cmp(const void* a, const void* b){
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    if (ea->w < eb->w) return -1;
    else if (ea->w > eb->w) return 1;
    else return 0;
}

int cmp_desc(const void* a, const void* b){
    double da = *(double*)a;
    double db = *(double*)b;
    if (da > db) return -1;
    else if (da < db) return 1;
    else return 0;
}

int find_set(int* parent, int x){
    if (parent[x] != x)
        parent[x] = find_set(parent, parent[x]);
    return parent[x];
}

int main(){
    int S, P;
    scanf("%d %d", &S, &P);
    int (*points)[2] = malloc(sizeof(int)*2*P);
    for(int i=0;i<P;i++) scanf("%d %d", &points[i][0], &points[i][1]);
    
    int max_edges = P*(P-1)/2;
    Edge* edges = malloc(sizeof(Edge)*max_edges);
    int idx=0;
    for(int i=0;i<P;i++) {
        for(int j=i+1;j<P;j++){
            double dx = points[i][0] - points[j][0];
            double dy = points[i][1] - points[j][1];
            double dist = sqrt(dx*dx + dy*dy);
            edges[idx].u = i;
            edges[idx].v = j;
            edges[idx].w = dist;
            idx++;
        }
    }
    qsort(edges, idx, sizeof(Edge), cmp);
    
    int* parent = malloc(sizeof(int)*P);
    for(int i=0;i<P;i++) parent[i]=i;
    
    double* mst = malloc(sizeof(double)*(P-1));
    int count=0;
    for(int i=0;i<idx && count < P-1;i++){
        int fu = find_set(parent, edges[i].u);
        int fv = find_set(parent, edges[i].v);
        if(fu != fv){
            parent[fu] = fv;
            mst[count++] = edges[i].w;
        }
    }
    
    if(S >= P){
        printf("0.00\n");
    }
    else{
        qsort(mst, count, sizeof(double), cmp_desc);
        double D;
        if(S-1 < count){
            D = mst[S-1];
        }
        else{
            D = 0.0;
        }
        printf("%.2lf\n", D);
    }
    
    free(points);
    free(edges);
    free(parent);
    free(mst);
    return 0;
}