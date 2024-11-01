#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(){
    int N;
    scanf("%d", &N);
    int adj[N][N];
    for(int i=0;i<N*N;i++){
        int num;
        scanf("%d", &num);
        adj[i/N][i%N] = num;
    }
    int inMST[N];
    int minEdge[N];
    for(int i=0;i<N;i++){
        inMST[i] = 0;
        minEdge[i] = INT32_MAX;
    }
    minEdge[0] = 0;
    long long total = 0;
    for(int i=0;i<N;i++){
        int u = -1;
        for(int v=0; v<N; v++) {
            if(!inMST[v] && (u == -1 || minEdge[v] < minEdge[u])) u = v;
        }
        if(minEdge[u] == INT32_MAX){
            // Not connected
            printf("-1\n");
            return 0;
        }
        inMST[u] = 1;
        total += minEdge[u];
        for(int v=0; v<N; v++){
            if(adj[u][v] < minEdge[v] && !inMST[v]){
                minEdge[v] = adj[u][v];
            }
        }
    }
    printf("%lld\n", total);
}