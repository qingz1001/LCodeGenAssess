#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 201
#define MAX_EDGES 10000
#define INF 1e18

typedef struct {
    int to;
    double weight;
} Edge;

typedef struct {
    double dist;
    int node;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

// Function to create a min heap
MinHeap* createHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Swap two heap nodes
void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up
void heapifyUp(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index -1)/2;
        if (heap->data[parent].dist > heap->data[index].dist) {
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        }
        else {
            break;
        }
    }
}

// Heapify down
void heapifyDown(MinHeap *heap, int index) {
    int smallest = index;
    while (1) {
        int left = 2*index +1;
        int right = 2*index +2;
        if (left < heap->size && heap->data[left].dist < heap->data[smallest].dist)
            smallest = left;
        if (right < heap->size && heap->data[right].dist < heap->data[smallest].dist)
            smallest = right;
        if (smallest != index) {
            swap(&heap->data[smallest], &heap->data[index]);
            index = smallest;
        }
        else {
            break;
        }
    }
}

// Push to heap
void pushHeap(MinHeap *heap, double dist, int node) {
    if (heap->size == heap->capacity) {
        heap->capacity *=2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode)*heap->capacity);
    }
    heap->data[heap->size].dist = dist;
    heap->data[heap->size].node = node;
    heapifyUp(heap, heap->size);
    heap->size++;
}

// Pop from heap
HeapNode popHeap(MinHeap *heap) {
    HeapNode top = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    heapifyDown(heap, 0);
    return top;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    double x[MAX_NODES], y_coord[MAX_NODES];
    for(int i=1;i<=n;i++) {
        scanf("%lf %lf", &x[i], &y_coord[i]);
    }
    // Initialize adjacency list
    Edge adj[MAX_NODES][MAX_EDGES];
    int adj_cnt[MAX_NODES];
    for(int i=1;i<=n;i++) adj_cnt[i]=0;
    for(int i=0;i<m;i++) {
        int p, q;
        scanf("%d %d", &p, &q);
        double dx = x[p] - x[q];
        double dy = y_coord[p] - y_coord[q];
        double dist = sqrt(dx*dx + dy*dy);
        adj[p][adj_cnt[p]].to = q;
        adj[p][adj_cnt[p]].weight = dist;
        adj_cnt[p]++;
        if(p != q){
            adj[q][adj_cnt[q]].to = p;
            adj[q][adj_cnt[q]].weight = dist;
            adj_cnt[q]++;
        }
    }
    // Initialize distances
    double first_dist[MAX_NODES];
    double second_dist_arr[MAX_NODES];
    for(int i=1;i<=n;i++) {
        first_dist[i] = INF;
        second_dist_arr[i] = INF;
    }
    first_dist[1]=0.0;
    // Create heap
    MinHeap *heap = createHeap(100000);
    pushHeap(heap, 0.0, 1);
    while(heap->size >0){
        HeapNode current = popHeap(heap);
        double dist = current.dist;
        int u = current.node;
        // If the current distance is greater than second_dist, skip
        if(dist > second_dist_arr[u]) continue;
        for(int i=0;i<adj_cnt[u];i++){
            int v = adj[u][i].to;
            double w = adj[u][i].weight;
            double new_dist = dist + w;
            if(new_dist < first_dist[v] - 1e-9){
                second_dist_arr[v] = first_dist[v];
                first_dist[v] = new_dist;
                pushHeap(heap, first_dist[v], v);
            }
            else if(new_dist > first_dist[v] + 1e-9 && new_dist < second_dist_arr[v] -1e-9){
                second_dist_arr[v] = new_dist;
                pushHeap(heap, second_dist_arr[v], v);
            }
            else if (fabs(new_dist - first_dist[v]) < 1e-9 && new_dist < second_dist_arr[v] -1e-9){
                second_dist_arr[v] = new_dist;
                pushHeap(heap, second_dist_arr[v], v);
            }
        }
    }
    if(second_dist_arr[n] < INF){
        printf("%.2lf\n", second_dist_arr[n]+1e-8);
    }
    else{
        printf("-1\n");
    }
    // Free heap memory
    free(heap->data);
    free(heap);
    return 0;
}