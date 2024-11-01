#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    Edge** adj = (Edge**)calloc(n+1, sizeof(Edge*));
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        Edge* e = (Edge*)malloc(sizeof(Edge));
        e->to = v;
        e->weight = w;
        e->next = adj[u];
        adj[u] = e;
    }
    
    ll* dp = (ll*)malloc((n+1)*sizeof(ll));
    for(int i=1;i<=n;i++) dp[i] = -1e18;
    dp[1] = 0;
    
    for(int u=1; u<=n; u++){
        if(dp[u] == -1e18) continue;
        Edge* e = adj[u];
        while(e){
            if(dp[e->to] < dp[u] + e->weight){
                dp[e->to] = dp[u] + e->weight;
            }
            e = e->next;
        }
    }
    
    if(dp[n] == -1e18) printf("-1\n");
    else printf("%lld\n", dp[n]);
    
    for(int i=1;i<=n;i++){
        Edge* e = adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(adj);
    free(dp);
    return 0;
}