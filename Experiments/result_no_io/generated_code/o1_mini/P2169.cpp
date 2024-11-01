#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int u, v, w;
} Edge;

int cmp_edge(const void* a, const void* b){
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    if (ea->u != eb->u)
        return ea->u - eb->u;
    return ea->v - eb->v;
}

typedef struct {
    int to;
    int w;
} Adj;

typedef struct {
    int size;
    int capacity;
    Adj* data;
} AdjList;

typedef struct {
    int node;
    int dist;
} HeapNode;

typedef struct {
    int size;
    int capacity;
    HeapNode* data;
} Heap;

Heap* create_heap(int capacity){
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->data = (HeapNode*)malloc(sizeof(HeapNode)*(capacity+1));
    return heap;
}

void swap(HeapNode* a, HeapNode* b){
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

void heap_push(Heap* heap, int node, int dist){
    heap->size++;
    heap->data[heap->size].node = node;
    heap->data[heap->size].dist = dist;
    int i = heap->size;
    while(i >1 && heap->data[i].dist < heap->data[i/2].dist){
        swap(&heap->data[i], &heap->data[i/2]);
        i /=2;
    }
}

HeapNode heap_pop(Heap* heap){
    HeapNode top = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    int i=1, smallest=i;
    while(1){
        int left = 2*i, right = 2*i+1;
        if(left <= heap->size && heap->data[left].dist < heap->data[smallest].dist)
            smallest = left;
        if(right <= heap->size && heap->data[right].dist < heap->data[smallest].dist)
            smallest = right;
        if(smallest != i){
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    Edge* edges = (Edge*)malloc(sizeof(Edge)*m);
    for(int i=0;i<m;i++) scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    qsort(edges, m, sizeof(Edge), cmp_edge);
    // Mark edges to set to zero if bidirectional
    int i=0;
    while(i<m){
        int a = edges[i].u;
        int b = edges[i].v;
        int j = i;
        // Find all edges with (a,b)
        while(j<m && edges[j].u == a && edges[j].v == b) j++;
        // Find edges with (b,a)
        int k = i;
        while(k<m && !(edges[k].u == b && edges[k].v == a)) k++;
        if(k < m && edges[k].u == b && edges[k].v == a){
            // Set all edges in (a,b) and (b,a) to zero
            for(int x=i; x<j; x++) edges[x].w = 0;
            int l = k;
            while(l<m && edges[l].u == b && edges[l].v == a) { edges[l].w = 0; l++; }
        }
        i = j;
    }
    // Build adjacency list
    AdjList* adj = (AdjList*)malloc(sizeof(AdjList)*(n+1));
    for(int i=1;i<=n;i++) { adj[i].size=0; adj[i].capacity=4; adj[i].data=(Adj*)malloc(sizeof(Adj)*4); }
    for(int i=0;i<m;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if(adj[u].size == adj[u].capacity){
            adj[u].capacity *=2;
            adj[u].data = (Adj*)realloc(adj[u].data, sizeof(Adj)*adj[u].capacity);
        }
        adj[u].data[adj[u].size].to = v;
        adj[u].data[adj[u].size].w = w;
        adj[u].size++;
    }
    free(edges);
    // Dijkstra's
    int* dist = (int*)malloc(sizeof(int)*(n+1));
    for(int i=1;i<=n;i++) dist[i] = INT_MAX;
    dist[1] = 0;
    Heap* heap = create_heap(n);
    heap_push(heap, 1, 0);
    while(heap->size >0){
        HeapNode current = heap_pop(heap);
        int u = current.node;
        int du = current.dist;
        if(u == n) break;
        if(du > dist[u]) continue;
        for(int i=0;i<adj[u].size;i++){
            int v = adj[u].data[i].to;
            int w = adj[u].data[i].w;
            if(du + w < dist[v]){
                dist[v] = du + w;
                heap_push(heap, v, dist[v]);
            }
        }
    }
    printf("%d\n", dist[n]);
    // Free memory
    for(int i=1;i<=n;i++) free(adj[i].data);
    free(adj);
    free(dist);
    free(heap->data);
    free(heap);
    return 0;
}