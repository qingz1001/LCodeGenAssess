#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge {
    int to;
    int w;
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

void heapPush(MinHeap* heap, int node, int dist) {
    if (heap->size + 1 > heap->capacity) return;
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
        if (heap->data[2*i].dist < heap->data[smallest].dist)
            smallest = 2*i;
        if (2*i+1 <= heap->size && heap->data[2*i+1].dist < heap->data[smallest].dist)
            smallest = 2*i+1;
        if (smallest != i) {
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int main(){
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    Edge** adj = (Edge**)calloc(n+1, sizeof(Edge*));
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        Edge* e1 = (Edge*)malloc(sizeof(Edge));
        e1->to = v;
        e1->w = w;
        e1->next = adj[u];
        adj[u] = e1;
        Edge* e2 = (Edge*)malloc(sizeof(Edge));
        e2->to = u;
        e2->w = w;
        e2->next = adj[v];
        adj[v] = e2;
    }
    int* dist = (int*)malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++) dist[i] = INT_MAX;
    dist[s] = 0;
    MinHeap* heap = createHeap(m*2+1);
    heapPush(heap, s, 0);
    while(heap->size > 0){
        HeapNode current = heapPop(heap);
        int u = current.node;
        if(u == t) break;
        Edge* e = adj[u];
        while(e){
            if(dist[e->to] > dist[u] + e->w){
                dist[e->to] = dist[u] + e->w;
                heapPush(heap, e->to, dist[e->to]);
            }
            e = e->next;
        }
    }
    printf("%d\n", dist[t]);
    // Free memory
    for(int i=1;i<=n;i++) {
        Edge* e = adj[i];
        while(e){
            Edge* temp = e;
            e = e->next;
            free(temp);
        }
    }
    free(adj);
    free(dist);
    free(heap->data);
    free(heap);
    return 0;
}