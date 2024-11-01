#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1002
#define MAXM 6000
#define INF 1000000000

typedef struct {
    int from;
    int to;
    int weight;
} Edge;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Edge edges[MAXM];
    int edge_count = 0;
    for(int i=0;i<m;i++){
        int u, v, b;
        scanf("%d %d %d", &u, &v, &b);
        edges[edge_count].from = v;
        edges[edge_count].to = u;
        edges[edge_count].weight = b;
        edge_count++;
    }
    for(int i=1;i<=n;i++){
        edges[edge_count].from = 0;
        edges[edge_count].to = i;
        edges[edge_count].weight = 0;
        edge_count++;
    }
    int total = n +1;
    int dist[MAXN];
    for(int i=0;i<=n;i++) dist[i] = INF;
    dist[0] = 0;
    for(int i=0;i<total-1;i++){
        int updated = 0;
        for(int j=0;j<edge_count;j++){
            int u = edges[j].from;
            int v = edges[j].to;
            int w = edges[j].weight;
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                updated = 1;
            }
        }
        if(!updated) break;
    }
    // Check for negative cycle
    int has_neg = 0;
    for(int j=0;j<edge_count;j++){
        int u = edges[j].from;
        int v = edges[j].to;
        int w = edges[j].weight;
        if(dist[u] + w < dist[v]){
            has_neg = 1;
            break;
        }
    }
    if(has_neg){
        printf("NO SOLUTION\n");
        return 0;
    }
    // Shift to make minimum zero
    int min = INF;
    for(int i=1;i<=n;i++) if(dist[i] < min) min = dist[i];
    // Ensure min is <=0
    // Since T_i >=0, min should be <=0
    for(int i=1;i<=n;i++) dist[i] -= min;
    for(int i=1;i<=n;i++) printf("%d\n", dist[i]);
    return 0;
}