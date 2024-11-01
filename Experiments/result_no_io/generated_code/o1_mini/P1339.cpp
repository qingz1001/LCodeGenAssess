#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

typedef struct {
    Edge* head;
} AdjList;

typedef struct {
    int node;
    int dist;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

AdjList adj[2501];
int dist_arr[2501];
int n, m, s, t;

// Heap functions
MinHeap* createMinHeap(int capacity){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * (capacity + 1));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode* a, HeapNode* b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap* heap, int idx){
    while(idx > 1){
        int parent = idx / 2;
        if(heap->data[parent].dist > heap->data[idx].dist){
            swap(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
        else break;
    }
}

void heapifyDown(MinHeap* heap, int idx){
    while(2 * idx <= heap->size){
        int smallest = idx;
        int left = 2 * idx;
        int right = 2 * idx + 1;
        if(left <= heap->size && heap->data[left].dist < heap->data[smallest].dist){
            smallest = left;
        }
        if(right <= heap->size && heap->data[right].dist < heap->data[smallest].dist){
            smallest = right;
        }
        if(smallest != idx){
            swap(&heap->data[smallest], &heap->data[idx]);
            idx = smallest;
        }
        else break;
    }
}

void insertHeap(MinHeap* heap, int node, int dist){
    if(heap->size + 1 > heap->capacity){
        return;
    }
    heap->size++;
    heap->data[heap->size].node = node;
    heap->data[heap->size].dist = dist;
    heapifyUp(heap, heap->size);
}

HeapNode extractMin(MinHeap* heap){
    HeapNode min = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    heapifyDown(heap, 1);
    return min;
}

int isEmpty(MinHeap* heap){
    return heap->size == 0;
}

int main(){
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        Edge* e1 = (Edge*)malloc(sizeof(Edge));
        e1->to = v;
        e1->weight = w;
        e1->next = adj[u].head;
        adj[u].head = e1;
        Edge* e2 = (Edge*)malloc(sizeof(Edge));
        e2->to = u;
        e2->weight = w;
        e2->next = adj[v].head;
        adj[v].head = e2;
    }
    for(int i=1;i<=n;i++) dist_arr[i] = INT_MAX;
    dist_arr[s] = 0;
    MinHeap* heap = createMinHeap(m*2);
    insertHeap(heap, s, 0);
    while(!isEmpty(heap)){
        HeapNode current = extractMin(heap);
        int u = current.node;
        int d = current.dist;
        if(u == t){
            break;
        }
        if(d > dist_arr[u]) continue;
        Edge* e = adj[u].head;
        while(e){
            int v = e->to;
            int w = e->weight;
            if(dist_arr[v] > dist_arr[u] + w){
                dist_arr[v] = dist_arr[u] + w;
                insertHeap(heap, v, dist_arr[v]);
            }
            e = e->next;
        }
    }
    printf("%d\n", dist_arr[t]);
    return 0;
}