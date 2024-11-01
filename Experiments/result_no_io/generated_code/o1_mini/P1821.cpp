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
    Edge** adj;
    int n;
} Graph;

Graph* createGraph(int n) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->n = n;
    g->adj = (Edge**)calloc(n + 1, sizeof(Edge*));
    return g;
}

void addEdge(Graph* g, int from, int to, int w) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->weight = w;
    e->next = g->adj[from];
    g->adj[from] = e;
}

typedef struct {
    int node;
    int dist;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc((capacity + 1) * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapPush(MinHeap* heap, int node, int dist) {
    if (heap->size >= heap->capacity) return;
    heap->size++;
    heap->data[heap->size].node = node;
    heap->data[heap->size].dist = dist;
    int i = heap->size;
    while (i > 1 && heap->data[i].dist < heap->data[i/2].dist) {
        swap(&heap->data[i], &heap->data[i/2]);
        i /= 2;
    }
}

HeapNode heapPop(MinHeap* heap) {
    HeapNode top = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    int i = 1;
    while (2*i <= heap->size) {
        int smallest = i;
        if (heap->data[2*i].dist < heap->data[smallest].dist) smallest = 2*i;
        if (2*i+1 <= heap->size && heap->data[2*i+1].dist < heap->data[smallest].dist) smallest = 2*i+1;
        if (smallest != i) {
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int isEmpty(MinHeap* heap) {
    return heap->size == 0;
}

int* dijkstra(Graph* g, int start) {
    int n = g->n;
    int* dist = (int*)malloc((n + 1) * sizeof(int));
    for(int i=1;i<=n;i++) dist[i] = INT32_MAX/2;
    dist[start] = 0;
    MinHeap* heap = createHeap(n);
    heapPush(heap, start, 0);
    while(!isEmpty(heap)) {
        HeapNode current = heapPop(heap);
        int u = current.node;
        if(current.dist > dist[u]) continue;
        Edge* e = g->adj[u];
        while(e) {
            int v = e->to;
            if(dist[v] > dist[u] + e->weight) {
                dist[v] = dist[u] + e->weight;
                heapPush(heap, v, dist[v]);
            }
            e = e->next;
        }
    }
    free(heap->data);
    free(heap);
    return dist;
}

int main(){
    int n, m, x;
    scanf("%d %d %d", &n, &m, &x);
    Graph* g = createGraph(n);
    Graph* gr = createGraph(n);
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(g, u, v, w);
        addEdge(gr, v, u, w);
    }
    int* dist_from_x = dijkstra(g, x);
    int* dist_to_x = dijkstra(gr, x);
    int max_dist = 0;
    for(int i=1;i<=n;i++){
        if(dist_from_x[i] + dist_to_x[i] > max_dist){
            max_dist = dist_from_x[i] + dist_to_x[i];
        }
    }
    printf("%d\n", max_dist);
    // Free memory
    for(int i=1;i<=n;i++){
        Edge* e = g->adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
        e = gr->adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(g->adj);
    free(gr->adj);
    free(g);
    free(gr);
    free(dist_from_x);
    free(dist_to_x);
    return 0;
}