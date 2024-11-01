#include <stdio.h>
#include <stdlib.h>

int adj[51][51];
int adj_size[51];
int path[51];
int n, m;

int compare(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

void backtrack(int pos, int current, unsigned long long visited){
    if(pos == n){
        // Check if there's an edge from current to 1
        for(int i = 0; i < adj_size[current]; i++){
            if(adj[current][i] == 1){
                for(int j = 0; j < n; j++){
                    printf("%d%c", path[j], j == n-1 ? '\n' : ' ');
                }
                break;
            }
        }
        return;
    }
    for(int i = 0; i < adj_size[current]; i++){
        int next = adj[current][i];
        if(!((visited >> (next-1)) & 1)){
            path[pos] = next;
            backtrack(pos+1, next, visited | (1ULL << (next-1)));
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][adj_size[u]++] = v;
    }
    for(int u = 1; u <= n; u++){
        qsort(adj[u], adj_size[u], sizeof(int), compare);
    }
    path[0] = 1;
    backtrack(1, 1, 1ULL);
    return 0;
}