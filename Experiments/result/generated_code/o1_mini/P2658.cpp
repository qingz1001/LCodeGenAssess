#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int u;
    int v;
    long long w;
} Edge;

int M, N;
long long elevations[500][500];
int markers[500][500];
Edge edges[1000000];
int edge_count = 0;
int parent_size;
int parent_arr[250000];
int rank_arr_store[250000];
int marker_count_store[250000];

int find_set(int x){
    if(parent_arr[x] != x){
        parent_arr[x] = find_set(parent_arr[x]);
    }
    return parent_arr[x];
}

void union_set_func(int x, int y, int *total_marker_sets){
    int fx = find_set(x);
    int fy = find_set(y);
    if(fx == fy) return;
    if(rank_arr_store[fx] < rank_arr_store[fy]){
        parent_arr[fx] = fy;
        marker_count_store[fy] += marker_count_store[fx];
        if(marker_count_store[fx] >0 && marker_count_store[fy] > marker_count_store[fx]){
            (*total_marker_sets)--;
        }
    }
    else{
        parent_arr[fy] = fx;
        marker_count_store[fx] += marker_count_store[fy];
        if(marker_count_store[fy] >0 && marker_count_store[fx] > marker_count_store[fy]){
            (*total_marker_sets)--;
        }
        if(rank_arr_store[fx] == rank_arr_store[fy]){
            rank_arr_store[fx]++;
        }
    }
}

int cmp_edges(const void *a, const void *b){
    Edge *ea = (Edge *)a;
    Edge *eb = (Edge *)b;
    if(ea->w < eb->w) return -1;
    else if(ea->w > eb->w) return 1;
    else return 0;
}

int main(){
    scanf("%d %d", &M, &N);
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            scanf("%lld", &elevations[i][j]);
        }
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            scanf("%d", &markers[i][j]);
        }
    }
    // Collect edges
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            if(j+1 < N){
                Edge e;
                e.u = i*N + j;
                e.v = i*N + (j+1);
                e.w = llabs(elevations[i][j] - elevations[i][j+1]);
                edges[edge_count++] = e;
            }
            if(i+1 < M){
                Edge e;
                e.u = i*N + j;
                e.v = (i+1)*N + j;
                e.w = llabs(elevations[i][j] - elevations[i+1][j]);
                edges[edge_count++] = e;
            }
        }
    }
    // Sort edges
    qsort(edges, edge_count, sizeof(Edge), cmp_edges);
    // Initialize Union-Find
    parent_size = M*N;
    for(int i=0;i<parent_size;i++){
        parent_arr[i] = i;
        rank_arr_store[i] = 0;
        if(markers[i / N][i % N]){
            marker_count_store[i] = 1;
        }
        else{
            marker_count_store[i] = 0;
        }
    }
    // Count total marker sets
    int total_marker_sets = 0;
    for(int i=0;i<parent_size;i++){
        if(markers[i / N][i % N]){
            total_marker_sets++;
        }
    }
    // Krusky's algorithm
    long long D = 0;
    for(int i=0;i<edge_count;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        long long w = edges[i].w;
        int fu = find_set(u);
        int fv = find_set(v);
        if(fu != fv){
            if(marker_count_store[fu] >0 && marker_count_store[fv] >0){
                total_marker_sets--;
            }
            if(rank_arr_store[fu] < rank_arr_store[fv]){
                parent_arr[fu] = fv;
                marker_count_store[fv] += marker_count_store[fu];
            }
            else{
                parent_arr[fv] = fu;
                marker_count_store[fu] += marker_count_store[fv];
                if(rank_arr_store[fu] == rank_arr_store[fv]){
                    rank_arr_store[fu]++;
                }
            }
            if(marker_count_store[fu] >0 && marker_count_store[fv] >0 && fu != fv){
                // already decreased total_marker_sets above
            }
            if(total_marker_sets == 1){
                D = w;
                break;
            }
        }
    }
    printf("%lld\n", D);
    return 0;
}