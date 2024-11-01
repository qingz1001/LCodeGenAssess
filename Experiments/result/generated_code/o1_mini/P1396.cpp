#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10005
#define MAX_M 20005
#define INF 1000000000

typedef struct Edge {
    int to;
    int w;
    struct Edge *next;
} Edge;

typedef struct {
    int node;
    int max_w;
} HeapElement;

// Heap implementation
typedef struct {
    HeapElement *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapElement*)malloc(sizeof(HeapElement) * (capacity + 1));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapElement *a, HeapElement *b) {
    HeapElement temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap* heap, int idx) {
    while (idx > 1) {
        int parent = idx / 2;
        if (heap->data[parent].max_w > heap->data[idx].max_w) {
            swap(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
        else break;
    }
}

void heapify_down(MinHeap* heap, int idx) {
    while (2 * idx <= heap->size) {
        int smallest = idx;
        int left = 2 * idx;
        int right = 2 * idx + 1;
        if (left <= heap->size && heap->data[left].max_w < heap->data[smallest].max_w)
            smallest = left;
        if (right <= heap->size && heap->data[right].max_w < heap->data[smallest].max_w)
            smallest = right;
        if (smallest != idx) {
            swap(&heap->data[smallest], &heap->data[idx]);
            idx = smallest;
        }
        else break;
    }
}

void insertHeap(MinHeap* heap, HeapElement elem) {
    if (heap->size >= heap->capacity) return;
    heap->size++;
    heap->data[heap->size] = elem;
    heapify_up(heap, heap->size);
}

HeapElement extractMin(MinHeap* heap) {
    HeapElement min = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    heapify_down(heap, 1);
    return min;
}

int main(){
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    
    Edge* graph[MAX_N];
    for(int i=1;i<=n;i++) graph[i] = NULL;
    
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = v;
        edge1->w = w;
        edge1->next = graph[u];
        graph[u] = edge1;
        
        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = u;
        edge2->w = w;
        edge2->next = graph[v];
        graph[v] = edge2;
    }
    
    int dist[MAX_N];
    for(int i=1;i<=n;i++) dist[i] = INF;
    dist[s] = 0;
    
    MinHeap* heap = createHeap(m * 2);
    HeapElement start;
    start.node = s;
    start.max_w = 0;
    insertHeap(heap, start);
    
    while(heap->size > 0){
        HeapElement current = extractMin(heap);
        int u = current.node;
        int curr_max = current.max_w;
        if(u == t){
            printf("%d\n", curr_max);
            return 0;
        }
        if(curr_max > dist[u]) continue;
        Edge* e = graph[u];
        while(e != NULL){
            int v = e->to;
            int new_max = (curr_max > e->w) ? curr_max : e->w;
            if(new_max < dist[v]){
                dist[v] = new_max;
                HeapElement elem;
                elem.node = v;
                elem.max_w = new_max;
                insertHeap(heap, elem);
            }
            e = e->next;
        }
    }
    return 0;
}