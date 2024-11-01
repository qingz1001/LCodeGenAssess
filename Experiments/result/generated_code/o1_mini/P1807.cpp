#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Edge** adj = calloc(n+1, sizeof(Edge*));
    int* indegree = calloc(n+1, sizeof(int));
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        Edge* edge = malloc(sizeof(Edge));
        edge->to = v;
        edge->weight = w;
        edge->next = adj[u];
        adj[u] = edge;
        indegree[v]++;
    }
    int* queue = malloc((n+1)*sizeof(int));
    int front=0, rear=0;
    for(int i=1;i<=n;i++) if(indegree[i]==0) queue[rear++] = i;
    int* topo = malloc(n*sizeof(int));
    int idx=0;
    while(front < rear){
        int u = queue[front++];
        topo[idx++] = u;
        for(Edge* e = adj[u]; e != NULL; e = e->next){
            indegree[e->to]--;
            if(indegree[e->to]==0){
                queue[rear++] = e->to;
            }
        }
    }
    free(queue);
    free(indegree);
    long long* dist = malloc((n+1)*sizeof(long long));
    for(int i=1;i<=n;i++) dist[i] = LLONG_MIN;
    dist[1] = 0;
    for(int i=0;i<idx;i++){
        int u = topo[i];
        if(dist[u] == LLONG_MIN) continue;
        for(Edge* e = adj[u]; e != NULL; e = e->next){
            if(dist[e->to] < dist[u] + e->weight){
                dist[e->to] = dist[u] + e->weight;
            }
        }
    }
    if(dist[n] == LLONG_MIN) printf("-1\n");
    else printf("%lld\n", dist[n]);
    for(int i=1;i<=n;i++) {
        Edge* e = adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(adj);
    free(topo);
    free(dist);
}