#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000001
#define MAX_M 2000000
#define INF 1000000000000000000LL

typedef long long ll;

typedef struct {
    int to;
    ll w;
    int next;
} Edge;

typedef struct {
    int node;
    ll dist;
} HeapItem;

Edge edges1[MAX_M];
Edge edges2[MAX_M];
int head1[MAX_N];
int head2[MAX_N];
ll dist1_arr[MAX_N];
ll dist2_arr[MAX_N];

HeapItem heap1[MAX_M];
int heap_size1;

HeapItem heap2[MAX_M];
int heap_size2;

void dijkstra(int n, Edge* edges, int* head, ll* dist) {
    for(int i=1;i<=n;i++) dist[i] = INF;
    dist[1] = 0;
    heap_size1 = 0;
    heap1[heap_size1].node = 1;
    heap1[heap_size1].dist = 0;
    heap_size1++;

    while(heap_size1 > 0){
        // Extract min
        int min_idx = 0;
        for(int i=1;i<heap_size1;i++) {
            if(heap1[i].dist < heap1[min_idx].dist) min_idx = i;
        }
        HeapItem current = heap1[min_idx];
        heap_size1--;
        heap1[min_idx] = heap1[heap_size1];
        
        if(current.dist > dist[current.node]) continue;
        
        // Traverse edges
        int u = current.node;
        for(int e = head[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            ll w = edges[e].w;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                heap1[heap_size1].node = v;
                heap1[heap_size1].dist = dist[v];
                heap_size1++;
            }
        }
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) { head1[i] = -1; head2[i] = -1; }
    int edge1_cnt=0, edge2_cnt=0;
    for(int i=0;i<m;i++){
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        edges1[edge1_cnt].to = v;
        edges1[edge1_cnt].w = w;
        edges1[edge1_cnt].next = head1[u];
        head1[u] = edge1_cnt++;
        
        edges2[edge2_cnt].to = u;
        edges2[edge2_cnt].w = w;
        edges2[edge2_cnt].next = head2[v];
        head2[v] = edge2_cnt++;
    }
    
    dijkstra(n, edges1, head1, dist1_arr);
    dijkstra(n, edges2, head2, dist2_arr);
    
    ll total = 0;
    for(int i=1;i<=n;i++) total += dist1_arr[i] + dist2_arr[i];
    printf("%lld\n", total);
    return 0;
}