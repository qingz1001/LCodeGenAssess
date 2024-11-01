#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

// Initialize the heap with a given capacity
void heap_init(MinHeap *heap, int capacity) {
    heap->data = (int *)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
}

// Push a value into the heap
void heap_push(MinHeap *heap, int val) {
    int i = heap->size;
    heap->data[i] = val;
    heap->size++;
    // Heapify up
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent] > heap->data[i]) {
            int temp = heap->data[parent];
            heap->data[parent] = heap->data[i];
            heap->data[i] = temp;
            i = parent;
        }
        else {
            break;
        }
    }
}

// Pop the minimum value from the heap
int heap_pop(MinHeap *heap) {
    if (heap->size == 0) return -1; // Should not happen
    int min_val = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    // Heapify down
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            int temp = heap->data[smallest];
            heap->data[smallest] = heap->data[i];
            heap->data[i] = temp;
            i = smallest;
        }
        else {
            break;
        }
    }
    return min_val;
}

// Free the heap memory
void heap_free(MinHeap *heap) {
    free(heap->data);
}

// Function to check if a given K is possible
int is_possible(int K, int N, int T_max, int *d) {
    MinHeap heap;
    heap_init(&heap, K);
    for(int i = 0; i < K && i < N; i++) {
        heap_push(&heap, d[i]);
    }
    for(int i = K; i < N; i++) {
        int earliest = heap_pop(&heap);
        int new_finish = earliest + d[i];
        if(new_finish > T_max) {
            heap_free(&heap);
            return 0;
        }
        heap_push(&heap, new_finish);
    }
    // Find the maximum finish time in the heap
    int max_time = 0;
    for(int i = 0; i < heap.size; i++) {
        if(heap.data[i] > max_time) {
            max_time = heap.data[i];
        }
    }
    heap_free(&heap);
    return max_time <= T_max;
}

int main(){
    int N, T_max;
    scanf("%d %d", &N, &T_max);
    int *d = (int *)malloc(sizeof(int) * N);
    for(int i = 0; i < N; i++) {
        scanf("%d", &d[i]);
    }
    int left = 1, right = N;
    while(left < right){
        int mid = left + (right - left) / 2;
        if(is_possible(mid, N, T_max, d)){
            right = mid;
        }
        else{
            left = mid + 1;
        }
    }
    printf("%d\n", left);
    free(d);
    return 0;
}