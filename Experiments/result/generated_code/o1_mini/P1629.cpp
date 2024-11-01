#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 1001
#define MAX_EDGES_PER_NODE 1000
#define INF 100000000000000LL

typedef long long ll;

typedef struct {
    int to;
    int weight;
} Edge;

typedef struct {
    Edge edges[MAX_EDGES_PER_NODE];
    int size;
} AdjList;

typedef struct {
    int node;
    ll dist;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

void swap(HeapNode *a, HeapNode *b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

MinHeap* createMinHeap(int capacity){
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void pushHeap(MinHeap *heap, int node, ll dist){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode)*heap->capacity);
    }
    int i = heap->size++;
    heap->data[i].node = node;
    heap->data[i].dist = dist;
    while(i != 0){
        int parent = (i -1)/2;
        if(heap->data[parent].dist <= heap->data[i].dist) break;
        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

HeapNode popHeap(MinHeap *heap){
    HeapNode top = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    int i = 0;
    while(1){
        int smallest = i;
        int left = 2*i +1;
        int right = 2*i +2;
        if(left < heap->size && heap->data[left].dist < heap->data[smallest].dist){
            smallest = left;
        }
        if(right < heap->size && heap->data[right].dist < heap->data[smallest].dist){
            smallest = right;
        }
        if(smallest != i){
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

ll* dijkstra(int n, AdjList adj[], int start){
    ll *dist = (ll*)malloc(sizeof(ll)*(n+1));
    for(int i=1;i<=n;i++) dist[i] = INF;
    dist[start] = 0;
    MinHeap *heap = createMinHeap(n);
    pushHeap(heap, start, 0);
    while(heap->size >0){
        HeapNode current = popHeap(heap);
        int u = current.node;
        ll d = current.dist;
        if(d > dist[u]) continue;
        for(int i=0;i<adj[u].size;i++){
            int v = adj[u].edges[i].to;
            ll w = adj[u].edges[i].weight;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pushHeap(heap, v, dist[v]);
            }
        }
    }
    free(heap->data);
    free(heap);
    return dist;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    AdjList adj_forward[MAX_N];
    AdjList adj_reverse[MAX_N];
    for(int i=1;i<=n;i++){
        adj_forward[i].size = 0;
        adj_reverse[i].size = 0;
    }
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if(adj_forward[u].size < MAX_EDGES_PER_NODE){
            adj_forward[u].edges[adj_forward[u].size].to = v;
            adj_forward[u].edges[adj_forward[u].size].weight = w;
            adj_forward[u].size++;
        }
        if(adj_reverse[v].size < MAX_EDGES_PER_NODE){
            adj_reverse[v].edges[adj_reverse[v].size].to = u;
            adj_reverse[v].edges[adj_reverse[v].size].weight = w;
            adj_reverse[v].size++;
        }
    }
    ll *dist_forward = dijkstra(n, adj_forward, 1);
    ll *dist_backward = dijkstra(n, adj_reverse, 1);
    ll sum =0;
    for(int i=2;i<=n;i++) sum += dist_forward[i] + dist_backward[i];
    printf("%lld\n", sum);
    free(dist_forward);
    free(dist_backward);
    return 0;
}