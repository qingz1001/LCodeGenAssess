#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5005

typedef struct Node {
    int parent;
    int rank;
} Node;

Node uf[MAXN];

int find_set(int x){
    if(uf[x].parent != x)
        uf[x].parent = find_set(uf[x].parent);
    return uf[x].parent;
}

void union_set(int x, int y){
    int fx = find_set(x);
    int fy = find_set(y);
    if(fx == fy) return;
    if(uf[fx].rank < uf[fy].rank){
        uf[fx].parent = fy;
    }
    else{
        uf[fy].parent = fx;
        if(uf[fx].rank == uf[fy].rank)
            uf[fx].rank++;
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0;i<=n;i++){
        uf[i].parent = i;
        uf[i].rank = 0;
    }
    // To handle deletions, we need to track existing edges
    // We'll use adjacency lists
    // Since n <= 5000, we can use a matrix
    char **adj = (char**)malloc((n+1)*sizeof(char*));
    for(int i=0;i<=n;i++){
        adj[i] = (char*)calloc(n+1, sizeof(char));
    }
    long last = 0;
    for(int i=0;i<m;i++){
        int op;
        long x, y;
        scanf("%d %ld %ld", &op, &x, &y);
        int u = x ^ last;
        int v = y ^ last;
        if(u < 1) u = 1;
        if(u > n) u = n;
        if(v < 1) v = 1;
        if(v > n) v = n;
        if(op == 0){
            if(!adj[u][v]){
                adj[u][v] = adj[v][u] = 1;
                union_set(u, v);
            }
        }
        else if(op == 1){
            if(adj[u][v]){
                adj[u][v] = adj[v][u] = 0;
                // Rebuild UF
                for(int j=1;j<=n;j++){
                    uf[j].parent = j;
                    uf[j].rank = 0;
                }
                for(int a=1;a<=n;a++){
                    for(int b=a+1;b<=n;b++){
                        if(adj[a][b]){
                            union_set(a, b);
                        }
                    }
                }
            }
        }
        else if(op == 2){
            if(find_set(u) == find_set(v)){
                printf("Y\n");
                last = u;
            }
            else{
                printf("N\n");
                last = v;
            }
        }
    }
    for(int i=0;i<=n;i++) free(adj[i]);
    free(adj);
    return 0;
}