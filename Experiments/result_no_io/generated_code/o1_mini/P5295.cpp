#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 502
#define MAX_M 1002

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, m;
        scanf("%d %d", &n, &m);
        // Initialize adjacency lists
        int adj[MAX_N][MAX_M];
        int adj_size[MAX_N];
        for(int i=1;i<=n;i++) adj_size[i]=0;
        for(int i=0;i<m;i++){
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u][adj_size[u]++] = v;
            adj[v][adj_size[v]++] = u;
        }
        // Initialize degrees and removed flags
        int degree[MAX_N];
        bool removed[MAX_N];
        for(int i=1;i<=n;i++){
            degree[i] = adj_size[i];
            removed[i] = false;
        }
        int c =0;
        for(int i=1;i<=n;i++){
            // Find vertex with minimum degree
            int min_deg = -1;
            int v = -1;
            for(int j=1;j<=n;j++) {
                if(!removed[j]){
                    if(min_deg == -1 || degree[j]<min_deg){
                        min_deg = degree[j];
                        v = j;
                    }
                }
            }
            if(v == -1) break;
            if(min_deg > c) c = min_deg;
            removed[v] = true;
            // Decrease degree of neighbors
            for(int k=0;k<adj_size[v];k++){
                int u = adj[v][k];
                if(!removed[u]){
                    degree[u]--;
                }
            }
        }
        if(c <=2) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}