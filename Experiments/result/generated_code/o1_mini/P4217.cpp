#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int j;
    ll cost;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

// Initialize the heap
MinHeap* initHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * (capacity + 1));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Swap two heap nodes
void swapHeapNode(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Percolate up
void heapify_up(MinHeap *heap, int idx) {
    while (idx > 1) {
        int parent = idx / 2;
        if (heap->data[parent].cost > heap->data[idx].cost) {
            swapHeapNode(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
        else break;
    }
}

// Percolate down
void heapify_down(MinHeap *heap, int idx) {
    while (2 * idx <= heap->size) {
        int smallest = idx;
        int left = 2 * idx;
        int right = 2 * idx + 1;
        if (left <= heap->size && heap->data[left].cost < heap->data[smallest].cost)
            smallest = left;
        if (right <= heap->size && heap->data[right].cost < heap->data[smallest].cost)
            smallest = right;
        if (smallest != idx) {
            swapHeapNode(&heap->data[smallest], &heap->data[idx]);
            idx = smallest;
        }
        else break;
    }
}

// Push a new node to the heap
void pushHeap(MinHeap *heap, int j, ll cost) {
    if (heap->size + 1 > heap->capacity) {
        heap->capacity *= 2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode) * (heap->capacity + 1));
    }
    heap->size++;
    heap->data[heap->size].j = j;
    heap->data[heap->size].cost = cost;
    heapify_up(heap, heap->size);
}

// Pop the top node from the heap
HeapNode popHeap(MinHeap *heap) {
    HeapNode top = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    heapify_down(heap, 1);
    return top;
}

int main(){
    int N;
    scanf("%d", &N);
    ll *D = (ll*)malloc(sizeof(ll)*(N+1));
    for(int i=1;i<=N;i++) scanf("%lld", &D[i]);
    ll *U = (ll*)malloc(sizeof(ll)*(N+1));
    for(int i=1;i<=N;i++) scanf("%lld", &U[i]);
    ll *P = (ll*)malloc(sizeof(ll)*(N+1));
    for(int i=1;i<=N;i++) scanf("%lld", &P[i]);
    ll *M = (ll*)malloc(sizeof(ll)*(N));
    for(int i=1;i<=N-1;i++) scanf("%lld", &M[i]);
    ll *C = (ll*)malloc(sizeof(ll)*(N));
    for(int i=1;i<=N-1;i++) scanf("%lld", &C[i]);
    ll *prefix_C = (ll*)malloc(sizeof(ll)*(N+2));
    prefix_C[0] = 0;
    for(int i=1;i<=N;i++) prefix_C[i] = prefix_C[i-1] + (i<=N-1? C[i] : 0);
    // Initialize heap
    MinHeap *heap = initHeap(N);
    ll total_cost = 0;
    for(int i=1;i<=N;i++){
        // Push current j=i
        ll cost_j = P[i] - prefix_C[i];
        pushHeap(heap, i, cost_j);
        ll demand = D[i];
        while(demand > 0){
            if(heap->size == 0){
                // This should not happen as per problem statement
                break;
            }
            HeapNode top = heap->data[1];
            int j = top.j;
            ll available = U[j];
            if(available == 0){
                // Remove this j
                popHeap(heap);
                continue;
            }
            ll assign = (demand < available) ? demand : available;
            total_cost += assign * (P[j] + prefix_C[i] - prefix_C[j]);
            U[j] -= assign;
            demand -= assign;
            if(U[j] == 0){
                popHeap(heap);
            }
        }
    }
    printf("%lld", total_cost);
    // Free memory
    free(D);
    free(U);
    free(P);
    free(M);
    free(C);
    free(prefix_C);
    free(heap->data);
    free(heap);
    return 0;
}