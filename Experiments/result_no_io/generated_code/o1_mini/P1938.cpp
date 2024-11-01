#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_C 220
#define MAX_E 500
#define INF -100000000000LL

typedef long long ll;

typedef struct {
    int u;
    int v;
    ll w;
} Edge;

int main(){
    int D, P, C, F, S;
    scanf("%d %d %d %d %d", &D, &P, &C, &F, &S);
    
    Edge edges[MAX_E];
    int edge_cnt = 0;
    
    // Read P paths
    for(int i=0;i<P;i++){
        int A, B;
        scanf("%d %d", &A, &B);
        edges[edge_cnt].u = A;
        edges[edge_cnt].v = B;
        edges[edge_cnt].w = D;
        edge_cnt++;
    }
    
    // Read F flights
    for(int i=0;i<F;i++){
        int J, K, T;
        scanf("%d %d %d", &J, &K, &T);
        edges[edge_cnt].u = J;
        edges[edge_cnt].v = K;
        edges[edge_cnt].w = (ll)D - (ll)T;
        edge_cnt++;
    }
    
    ll dist[MAX_C+1];
    for(int i=1;i<=C;i++) dist[i] = INF;
    dist[S] = 0;
    
    // Bellman-Ford
    for(int i=1;i<=C;i++){
        int updated = 0;
        for(int j=0;j<edge_cnt;j++){
            int u = edges[j].u;
            int v = edges[j].v;
            ll w = edges[j].w;
            if(dist[u] != INF && dist[v] < dist[u] + w){
                dist[v] = dist[u] + w;
                updated = 1;
            }
        }
        if(i == C && updated){
            printf("-1\n");
            return 0;
        }
        if(!updated) break;
    }
    
    // Find maximum
    ll max_profit = INF;
    for(int i=1;i<=C;i++) {
        if(dist[i] > max_profit) {
            max_profit = dist[i];
        }
        if(dist[i] > max_profit) {
            max_profit = dist[i];
        }
    }
    // Recompute maximum correctly
    max_profit = INF;
    for(int i=1;i<=C;i++) {
        if(dist[i] > max_profit){
            max_profit = dist[i];
        }
    }
    // Since INF is a large negative, ensure at least S is reachable
    printf("%lld\n", max_profit);
    return 0;
}