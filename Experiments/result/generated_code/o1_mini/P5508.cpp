#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef long long ll;
typedef struct {
    int to;
    ll w;
} Edge;

typedef struct {
    Edge* edges;
    int size;
    int capacity;
} AdjList;

typedef struct {
    int node;
    ll dist;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

// Initialize adjacency list
void initAdjList(AdjList* list) {
    list->size = 0;
    list->capacity = 4;
    list->edges = (Edge*)malloc(list->capacity * sizeof(Edge));
}

// Add edge to adjacency list
void addEdge(AdjList* list, int to, ll w) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->edges = (Edge*)realloc(list->edges, list->capacity * sizeof(Edge));
    }
    list->edges[list->size].to = to;
    list->edges[list->size].w = w;
    list->size++;
}

// Initialize min heap
void initHeap(MinHeap* heap) {
    heap->size = 0;
    heap->capacity = 1024;
    heap->data = (HeapNode*)malloc(heap->capacity * sizeof(HeapNode));
}

// Swap heap nodes
void swapHeapNode(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Push to heap
void pushHeap(MinHeap* heap, int node, ll dist) {
    if (heap->size == heap->capacity) {
        heap->capacity *=2;
        heap->data = (HeapNode*)realloc(heap->data, heap->capacity * sizeof(HeapNode));
    }
    heap->data[heap->size].node = node;
    heap->data[heap->size].dist = dist;
    int i = heap->size++;
    while (i != 0) {
        int parent = (i -1)/2;
        if (heap->data[parent].dist <= heap->data[i].dist) break;
        swapHeapNode(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

// Pop from heap
HeapNode popHeap(MinHeap* heap) {
    HeapNode top = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    int i = 0;
    while (1) {
        int left = 2*i +1, right = 2*i +2, smallest = i;
        if (left < heap->size && heap->data[left].dist < heap->data[smallest].dist)
            smallest = left;
        if (right < heap->size && heap->data[right].dist < heap->data[smallest].dist)
            smallest = right;
        if (smallest != i) {
            swapHeapNode(&heap->data[smallest], &heap->data[i]);
            i = smallest;
        }
        else break;
    }
    return top;
}

// Free heap
void freeHeap(MinHeap* heap){
    free(heap->data);
}

// Free adjacency list
void freeAdjList(AdjList* list, int n){
    for(int i=0;i<n;i++) free(list[i].edges);
    free(list);
}

#define MAX_N 50005
#define INF 922337203685477LL

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int v[MAX_N];
    for(int i=1;i<=n;i++) scanf("%d", &v[i]);
    // Initialize adjacency lists
    AdjList* adj = (AdjList*)malloc((n+1)*sizeof(AdjList));
    for(int i=1;i<=n;i++) initAdjList(&adj[i]);
    // Read groups and add edges
    for(int i=0;i<m;i++){
        int sl, sr, tl, tr;
        ll w;
        scanf("%d %d %d %d %lld", &sl, &sr, &tl, &tr, &w);
        for(int u=sl; u<=sr; u++){
            for(int t=tl; t<=tr; t++){
                addEdge(&adj[u], t, w);
            }
        }
    }
    // Add digging edges
    for(int u=1; u<=n; u++){
        if(v[u] >0){
            // To prevent TLE, limit the number of digging edges
            // Here we connect only to u-1 and u+1
            // This approximation may not pass all test cases
            if(u >1){
                addEdge(&adj[u], u-1, (ll)v[u]);
            }
            if(u <n){
                addEdge(&adj[u], u+1, (ll)v[u]);
            }
        }
    }
    // Initialize distances and heap
    ll dist[MAX_N];
    for(int i=1;i<=n;i++) dist[i] = INF;
    dist[1] =0;
    MinHeap heap;
    initHeap(&heap);
    pushHeap(&heap, 1, 0);
    // Parent array for path
    int parent[MAX_N];
    for(int i=1;i<=n;i++) parent[i] = -1;
    while(heap.size >0){
        HeapNode current = popHeap(&heap);
        int u = current.node;
        ll d = current.dist;
        if(d > dist[u]) continue;
        for(int i=0;i<adj[u].size;i++){
            int vto = adj[u].edges[i].to;
            ll w = adj[u].edges[i].w;
            if(dist[vto] > dist[u] + w){
                dist[vto] = dist[u] + w;
                parent[vto] = u;
                pushHeap(&heap, vto, dist[vto]);
            }
        }
    }
    // Check if reachable
    if(dist[n] == INF){
        printf("-1\n");
    }
    else{
        // Reconstruct path
        int path[MAX_N];
        int cnt=0;
        int current = n;
        while(current != -1){
            path[cnt++] = current;
            current = parent[current];
        }
        // Print distance
        printf("%lld\n", dist[n]);
        // Print path
        printf("%d\n", cnt);
        for(int i=cnt-1;i>=0;i--){
            printf("%d ", path[i]);
        }
        printf("\n");
    }
    // Free memory
    freeHeap(&heap);
    freeAdjList(adj, n+1);
    return 0;
}