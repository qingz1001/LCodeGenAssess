#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

typedef struct {
    int node;
    int dist;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

Edge* adj[1001];
Edge* adj_rev[1001];
int n, m;

// MinHeap functions
MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * (capacity + 1));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void pushHeap(MinHeap* heap, int node, int dist) {
    if (heap->size >= heap->capacity) return;
    heap->size++;
    heap->data[heap->size].node = node;
    heap->data[heap->size].dist = dist;
    int i = heap->size;
    while(i > 1 && heap->data[i].dist < heap->data[i/2].dist){
        swap(&heap->data[i], &heap->data[i/2]);
        i /=2;
    }
}

HeapNode popHeap(MinHeap* heap) {
    HeapNode top = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    int i = 1;
    while(2*i <= heap->size){
        int smallest = i;
        if(heap->data[2*i].dist < heap->data[smallest].dist){
            smallest = 2*i;
        }
        if(2*i+1 <= heap->size && heap->data[2*i+1].dist < heap->data[smallest].dist){
            smallest = 2*i+1;
        }
        if(smallest != i){
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int isEmpty(MinHeap* heap){
    return heap->size == 0;
}

// Dijkstra's algorithm
long long dijkstra(Edge* graph[], int start, int dist[]){
    for(int i=1;i<=n;i++) dist[i] = INT32_MAX;
    dist[start] = 0;
    MinHeap* heap = createHeap(n);
    pushHeap(heap, start, 0);
    while(!isEmpty(heap)){
        HeapNode current = popHeap(heap);
        int u = current.node;
        if(current.dist > dist[u]) continue;
        Edge* e = graph[u];
        while(e){
            int v = e->to;
            if(dist[u] + e->weight < dist[v]){
                dist[v] = dist[u] + e->weight;
                pushHeap(heap, v, dist[v]);
            }
            e = e->next;
        }
    }
    long long sum = 0;
    for(int i=2;i<=n;i++) {
        if(dist[i] == INT32_MAX) {
            // According to the problem, all nodes are reachable
            // So this should not happen
        }
        sum += dist[i];
    }
    free(heap->data);
    free(heap);
    return sum;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        Edge* new_edge = (Edge*)malloc(sizeof(Edge));
        new_edge->to = v;
        new_edge->weight = w;
        new_edge->next = adj[u];
        adj[u] = new_edge;
        
        // For reverse graph
        Edge* new_edge_rev = (Edge*)malloc(sizeof(Edge));
        new_edge_rev->to = u;
        new_edge_rev->weight = w;
        new_edge_rev->next = adj_rev[v];
        adj_rev[v] = new_edge_rev;
    }
    int dist1[1001];
    long long sum1 = dijkstra(adj, 1, dist1);
    int dist2[1001];
    long long sum2 = dijkstra(adj_rev, 1, dist2);
    long long total = 0;
    for(int i=2;i<=n;i++) {
        total += (long long)dist1[i] + (long long)dist2[i];
    }
    printf("%lld\n", total);
    // Free memory
    for(int i=1;i<=n;i++){
        Edge* e = adj[i];
        while(e){
            Edge* temp = e;
            e = e->next;
            free(temp);
        }
        e = adj_rev[i];
        while(e){
            Edge* temp = e;
            e = e->next;
            free(temp);
        }
    }
    return 0;
}