#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int u;
    int v;
    double dist;
} Edge;

int cmp(const void* a, const void* b){
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    if (ea->dist < eb->dist) return -1;
    if (ea->dist > eb->dist) return 1;
    return 0;
}

typedef struct {
    int parent;
    int rank;
} DSU;

int find_set(DSU* dsu, int x){
    if (dsu[x].parent != x)
        dsu[x].parent = find_set(dsu, dsu[x].parent);
    return dsu[x].parent;
}

void union_set(DSU* dsu, int x, int y){
    int fx = find_set(dsu, x);
    int fy = find_set(dsu, y);
    if (fx == fy) return;
    if (dsu[fx].rank < dsu[fy].rank){
        dsu[fx].parent = fy;
    }
    else{
        dsu[fy].parent = fx;
        if (dsu[fx].rank == dsu[fy].rank)
            dsu[fx].rank++;
    }
}

int main(){
    int S, P;
    scanf("%d %d", &S, &P);
    double coords[P][2];
    for(int i=0;i<P;i++) scanf("%lf %lf", &coords[i][0], &coords[i][1]);
    
    int total = P*(P-1)/2;
    Edge* edges = (Edge*)malloc(sizeof(Edge)*total);
    int idx=0;
    for(int i=0;i<P;i++) {
        for(int j=i+1;j<P;j++){
            double dx = coords[i][0] - coords[j][0];
            double dy = coords[i][1] - coords[j][1];
            edges[idx].u = i;
            edges[idx].v = j;
            edges[idx].dist = sqrt(dx*dx + dy*dy);
            idx++;
        }
    }
    
    qsort(edges, total, sizeof(Edge), cmp);
    
    DSU dsu[P];
    for(int i=0;i<P;i++){ dsu[i].parent = i; dsu[i].rank = 0; }
    
    // Build MST
    Edge mst[P-1];
    int mst_idx=0;
    for(int i=0;i<total && mst_idx < P-1;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        if(find_set(dsu, u) != find_set(dsu, v)){
            union_set(dsu, u, v);
            mst[mst_idx++] = edges[i];
        }
    }
    free(edges);
    
    if(S >= P){
        printf("0.00\n");
        return 0;
    }
    
    // Sort MST edges descendingly
    for(int i=0;i<mst_idx-1;i++){
        for(int j=i+1;j<mst_idx;j++){
            if(mst[i].dist < mst[j].dist){
                Edge temp = mst[i];
                mst[i] = mst[j];
                mst[j] = temp;
            }
        }
    }
    
    // The D is the (S-1)th largest edge
    double D = 0.0;
    if(S-1 < mst_idx){
        D = mst[S-2].dist;
    }
    
    printf("%.2lf\n", D);
    return 0;
}