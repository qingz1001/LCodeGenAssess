#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} Heap;

// Initialize heap
Heap* initHeap(int capacity, int isMinHeap) {
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (int*)malloc(sizeof(int) * (capacity + 1));
    heap->size = 0;
    heap->capacity = capacity;
    // isMinHeap determines the heap type
    // Not stored, handled in comparator
    return heap;
}

// Swap two integers
void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Comparator: returns 1 if a should come before b
int compare(int a, int b, int isMinHeap){
    if(isMinHeap)
        return a < b;
    else
        return a > b;
}

// Insert into heap
void insertHeap(Heap *heap, int val, int isMinHeap){
    heap->size++;
    heap->data[heap->size] = val;
    int idx = heap->size;
    while(idx > 1){
        int parent = idx / 2;
        if(compare(heap->data[idx], heap->data[parent], isMinHeap)){
            swap(&heap->data[idx], &heap->data[parent]);
            idx = parent;
        }
        else{
            break;
        }
    }
}

// Remove top of heap
int removeTop(Heap *heap, int isMinHeap){
    if(heap->size == 0) return -1;
    int top = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    int idx = 1;
    while(1){
        int left = 2 * idx;
        int right = 2 * idx + 1;
        int target = idx;
        if(left <= heap->size && compare(heap->data[left], heap->data[target], isMinHeap)){
            target = left;
        }
        if(right <= heap->size && compare(heap->data[right], heap->data[target], isMinHeap)){
            target = right;
        }
        if(target != idx){
            swap(&heap->data[idx], &heap->data[target]);
            idx = target;
        }
        else{
            break;
        }
    }
    return top;
}

int main(){
    int N;
    scanf("%d", &N);
    int *A = (int*)malloc(sizeof(int) * N);
    for(int i = 0; i < N; i++) scanf("%d", &A[i]);

    // Initialize two heaps
    Heap *maxHeap = initHeap(N, 0); // Max heap
    Heap *minHeap = initHeap(N, 1); // Min heap

    for(int i = 0; i < N; i++){
        if(maxHeap->size == 0 || A[i] <= maxHeap->data[1]){
            insertHeap(maxHeap, A[i], 0);
        }
        else{
            insertHeap(minHeap, A[i], 1);
        }

        // Balance the heaps
        if(maxHeap->size > minHeap->size + 1){
            int val = removeTop(maxHeap, 0);
            insertHeap(minHeap, val, 1);
        }
        else if(minHeap->size > maxHeap->size){
            int val = removeTop(minHeap, 1);
            insertHeap(maxHeap, val, 0);
        }

        // If current prefix length is odd
        if((i + 1) % 2 == 1){
            printf("%d\n", maxHeap->data[1]);
        }
    }

    // Free memory
    free(A);
    free(maxHeap->data);
    free(maxHeap);
    free(minHeap->data);
    free(minHeap);

    return 0;
}