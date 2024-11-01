#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u;
    int v;
    int w;
} Edge;

int cmp(const void* a, const void* b){
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    if(ea->w != eb->w) return ea->w - eb->w;
    if(ea->u != eb->u) return ea->u - eb->u;
    return ea->v - eb->v;
}

int main(){
    int N;
    scanf("%d", &N);
    int matrix[N][N];
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int max_edges = N*(N-1)/2;
    Edge* edges = (Edge*)malloc(sizeof(Edge)*max_edges);
    int idx=0;
    for(int i=0;i<N;i++) {
        for(int j=i+1;j<N;j++) {
            if(matrix[i][j] >0){
                edges[idx].u = i;
                edges[idx].v = j;
                edges[idx].w = matrix[i][j];
                idx++;
            }
        }
    }
    qsort(edges, idx, sizeof(Edge), cmp);
    int parent[N];
    for(int i=0;i<N;i++) parent[i] = i;
    int find_set(int x){
        if(parent[x] != x)
            parent[x] = find_set(parent[x]);
        return parent[x];
    }
    long long total =0;
    int count =0;
    for(int i=0;i<idx && count < N-1;i++) {
        int pu = find_set(edges[i].u);
        int pv = find_set(edges[i].v);
        if(pu != pv){
            parent[pu] = pv;
            total += edges[i].w;
            count++;
        }
    }
    printf("%lld\n", total);
    free(edges);
    return 0;
}