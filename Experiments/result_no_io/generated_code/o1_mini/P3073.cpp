#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int u;
    int v;
    int d;
} edge_t;

int cmp_edges(const void* a, const void* b) {
    edge_t* ea = (edge_t*)a;
    edge_t* eb = (edge_t*)b;
    if (ea->d != eb->d)
        return ea->d - eb->d;
    else {
        if (ea->u != eb->u)
            return ea->u - eb->u;
        else
            return ea->v - eb->v;
    }
}

int main(){
    int N;
    scanf("%d", &N);
    int size = N * N;
    int* h = (int*)malloc(sizeof(int) * size);
    for(int i=0;i<size;i++) {
        scanf("%d", &h[i]);
    }
    int max_edges = 2 * N * (N-1);
    edge_t* edges = (edge_t*)malloc(sizeof(edge_t) * max_edges);
    int edge_count = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int current = i*N + j;
            if(j < N-1){
                int right = i*N + (j+1);
                int diff = abs(h[current] - h[right]);
                edges[edge_count].u = current;
                edges[edge_count].v = right;
                edges[edge_count].d = diff;
                edge_count++;
            }
            if(i < N-1){
                int down = (i+1)*N + j;
                int diff = abs(h[current] - h[down]);
                edges[edge_count].u = current;
                edges[edge_count].v = down;
                edges[edge_count].d = diff;
                edge_count++;
            }
        }
    }
    free(h);
    qsort(edges, edge_count, sizeof(edge_t), cmp_edges);
    int* parent = (int*)malloc(sizeof(int) * size);
    int* sz = (int*)malloc(sizeof(int) * size);
    for(int i=0;i<size;i++){
        parent[i] = i;
        sz[i] = 1;
    }
    int required = (size +1)/2;
    int answer = 0;
    for(int i=0;i<edge_count;i++){
        // Find roots
        int u = edges[i].u;
        int v = edges[i].v;
        // Find with path compression
        int find_set = u;
        while(parent[find_set] != find_set){
            parent[find_set] = parent[parent[find_set]];
            find_set = parent[find_set];
        }
        int find_set_v = v;
        while(parent[find_set_v] != find_set_v){
            parent[find_set_v] = parent[parent[find_set_v]];
            find_set_v = parent[find_set_v];
        }
        if(find_set != find_set_v){
            // Union by size
            if(sz[find_set] < sz[find_set_v]){
                parent[find_set] = find_set_v;
                sz[find_set_v] += sz[find_set];
                if(sz[find_set_v] >= required){
                    answer = edges[i].d;
                    break;
                }
            }
            else{
                parent[find_set_v] = find_set;
                sz[find_set] += sz[find_set_v];
                if(sz[find_set] >= required){
                    answer = edges[i].d;
                    break;
                }
            }
        } else {
            if(sz[find_set] >= required){
                answer = edges[i].d;
                break;
            }
        }
    }
    // Edge case when N=1
    if(size ==1){
        answer =0;
    }
    printf("%d\n", answer);
    free(edges);
    free(parent);
    free(sz);
    return 0;
}