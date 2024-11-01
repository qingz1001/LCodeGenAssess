#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b){
    int aa = *(int*)a;
    int bb = *(int*)b;
    if (aa < bb) return -1;
    else if (aa > bb) return 1;
    else return 0;
}

long long count_intersection(int *a, int size_a, int *b, int size_b){
    long long count = 0;
    int i = 0, j = 0;
    while(i < size_a && j < size_b){
        if(a[i] < b[j]){
            i++;
        }
        else if(a[i] > b[j]){
            j++;
        }
        else{
            count++;
            i++;
            j++;
        }
    }
    return count;
}

int main(){
    int n, m;
    if(scanf("%d %d", &n, &m)!=2){
        return 0;
    }

    int *edge_u = (int*)malloc(m * sizeof(int));
    int *edge_v = (int*)malloc(m * sizeof(int));
    if(!edge_u || !edge_v){
        return 0;
    }

    int *degree = (int*)calloc(n+1, sizeof(int));
    if(!degree){
        free(edge_u);
        free(edge_v);
        return 0;
    }

    for(int i=0; i<m; i++){
        if(scanf("%d %d", &edge_u[i], &edge_v[i])!=2){
            free(edge_u);
            free(edge_v);
            free(degree);
            return 0;
        }
        degree[edge_u[i]]++;
        degree[edge_v[i]]++;
    }

    int *offset = (int*)malloc((n+2) * sizeof(int));
    if(!offset){
        free(edge_u);
        free(edge_v);
        free(degree);
        return 0;
    }

    offset[1] = 0;
    for(int i=1; i<=n; i++){
        offset[i+1] = offset[i] + degree[i];
    }

    int *adjacency = (int*)malloc(2*m * sizeof(int));
    if(!adjacency){
        free(edge_u);
        free(edge_v);
        free(degree);
        free(offset);
        return 0;
    }

    for(int i=0; i<=n; i++) degree[i] = 0;

    for(int i=0; i<m; i++){
        int u = edge_u[i];
        int v = edge_v[i];
        adjacency[offset[u] + degree[u]] = v;
        degree[u]++;
        adjacency[offset[v] + degree[v]] = u;
        degree[v]++;
    }

    for(int u=1; u<=n; u++){
        if(degree[u] > 0){
            qsort(adjacency + offset[u], degree[u], sizeof(int), cmpfunc);
        }
    }

    long long triangle_count = 0;
    for(int u=1; u<=n; u++){
        for(int i=0; i<degree[u]; i++){
            int v = adjacency[offset[u] + i];
            if(v > u){
                triangle_count += count_intersection(adjacency + offset[u], degree[u],
                                                    adjacency + offset[v], degree[v]);
            }
        }
    }

    printf("%lld\n", triangle_count);

    free(edge_u);
    free(edge_v);
    free(degree);
    free(offset);
    free(adjacency);
    return 0;
}