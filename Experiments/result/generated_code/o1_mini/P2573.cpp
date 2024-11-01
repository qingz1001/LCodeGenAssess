#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAXN 100005
#define MAXM 1000005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to;
    int cost;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int n, m;
int h[MAXN];
int order[MAXN];
int idx = 0;

// Comparator for sorting nodes in decreasing order of height
int cmp(const void* a, const void* b){
    int ia = *(int*)a;
    int ib = *(int*)b;
    if(h[ia] != h[ib]) return h[ib] - h[ia];
    return ia - ib;
}

typedef struct {
    int count;
    long long dist;
} DP;

DP dp[MAXN];

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &h[i]);
    for(int i=0;i<m;i++){
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        if(h[u] >= h[v]){
            Edge* e = (Edge*)malloc(sizeof(Edge));
            e->to = v;
            e->cost = k;
            e->next = adj[u];
            adj[u] = e;
        }
        if(h[v] >= h[u]){
            Edge* e = (Edge*)malloc(sizeof(Edge));
            e->to = u;
            e->cost = k;
            e->next = adj[v];
            adj[v] = e;
        }
    }
    for(int i=1;i<=n;i++) order[i-1] = i;
    qsort(order, n, sizeof(int), cmp);
    for(int i=1;i<=n;i++){
        dp[i].count = 0;
        dp[i].dist = INF;
    }
    dp[1].count = 1;
    dp[1].dist = 0;
    for(int i=0;i<n;i++){
        int u = order[i];
        if(dp[u].count == 0) continue;
        Edge* e = adj[u];
        while(e){
            int v = e->to;
            if(dp[v].count < dp[u].count + 1){
                dp[v].count = dp[u].count + 1;
                dp[v].dist = dp[u].dist + e->cost;
            }
            else if(dp[v].count == dp[u].count + 1 && dp[v].dist > dp[u].dist + e->cost){
                dp[v].dist = dp[u].dist + e->cost;
            }
            e = e->next;
        }
    }
    int max_count = 0;
    long long min_dist = INF;
    for(int i=1;i<=n;i++){
        if(dp[i].count > max_count){
            max_count = dp[i].count;
            min_dist = dp[i].dist;
        }
        else if(dp[i].count == max_count && dp[i].dist < min_dist){
            min_dist = dp[i].dist;
        }
    }
    printf("%d %lld\n", max_count, min_dist);
    // Free memory
    for(int i=1;i<=n;i++){
        Edge* e = adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    return 0;
}