#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int D;
    int u;
    int v;
} Edge;

int cmp(const void *a, const void *b) {
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    if (ea->D != eb->D)
        return ea->D - eb->D;
    return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    int total = N * N;
    int half = (total + 1) / 2;
    int *height = (int*)malloc(sizeof(int)*total);
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            scanf("%d", &height[i*N + j]);
        }
    }
    int max_edges = 2 * N * (N-1);
    Edge *edges = (Edge*)malloc(sizeof(Edge)*max_edges);
    int edge_count = 0;
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            int u = i*N + j;
            if(j+1 < N){
                int v = i*N + (j+1);
                int D = abs(height[u] - height[v]);
                edges[edge_count].D = D;
                edges[edge_count].u = u;
                edges[edge_count].v = v;
                edge_count++;
            }
            if(i+1 < N){
                int v = (i+1)*N + j;
                int D = abs(height[u] - height[v]);
                edges[edge_count].D = D;
                edges[edge_count].u = u;
                edges[edge_count].v = v;
                edge_count++;
            }
        }
    }
    qsort(edges, edge_count, sizeof(Edge), cmp);
    int *parent = (int*)malloc(sizeof(int)*total);
    int *size_set = (int*)malloc(sizeof(int)*total);
    for(int i=0;i<total;i++){
        parent[i] = i;
        size_set[i] = 1;
    }
    int result = 0;
    for(int i=0;i<edge_count;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        // Find root of u
        int root_u = u;
        while(parent[root_u] != root_u){
            parent[root_u] = parent[parent[root_u]];
            root_u = parent[root_u];
        }
        // Find root of v
        int root_v = v;
        while(parent[root_v] != root_v){
            parent[root_v] = parent[parent[root_v]];
            root_v = parent[root_v];
        }
        if(root_u != root_v){
            if(size_set[root_u] < size_set[root_v]){
                parent[root_u] = root_v;
                size_set[root_v] += size_set[root_u];
                if(size_set[root_v] >= half){
                    result = edges[i].D;
                    break;
                }
            }
            else{
                parent[root_v] = root_u;
                size_set[root_u] += size_set[root_v];
                if(size_set[root_u] >= half){
                    result = edges[i].D;
                    break;
                }
            }
        }
    }
    printf("%d\n", result);
    free(height);
    free(edges);
    free(parent);
    free(size_set);
    return 0;
}