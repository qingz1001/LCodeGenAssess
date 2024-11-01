#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

// Function to swap two integers
void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Initialize the heap
MinHeap* initHeap(int capacity){
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Percolate up
void heapPush(MinHeap *heap, int val){
    if(heap->size == heap->capacity){
        return;
    }
    heap->data[heap->size] = val;
    int i = heap->size;
    heap->size++;
    while(i > 0){
        int parent = (i - 1) / 2;
        if(heap->data[parent] > heap->data[i]){
            swap(&heap->data[parent], &heap->data[i]);
            i = parent;
        }
        else{
            break;
        }
    }
}

// Percolate down
int heapPop(MinHeap *heap){
    if(heap->size == 0){
        return -1;
    }
    int min = heap->data[0];
    heap->size--;
    if(heap->size > 0){
        heap->data[0] = heap->data[heap->size];
        int i = 0;
        while(1){
            int left = 2*i + 1;
            int right = 2*i + 2;
            int smallest = i;
            if(left < heap->size && heap->data[left] < heap->data[smallest]){
                smallest = left;
            }
            if(right < heap->size && heap->data[right] < heap->data[smallest]){
                smallest = right;
            }
            if(smallest != i){
                swap(&heap->data[i], &heap->data[smallest]);
                i = smallest;
            }
            else{
                break;
            }
        }
    }
    return min;
}

// Heapify the initial heap
void buildHeap(MinHeap *heap){
    for(int i = (heap->size / 2) - 1; i >= 0; i--){
        int current = i;
        while(1){
            int left = 2*current + 1;
            int right = 2*current + 2;
            int smallest = current;
            if(left < heap->size && heap->data[left] < heap->data[smallest]){
                smallest = left;
            }
            if(right < heap->size && heap->data[right] < heap->data[smallest]){
                smallest = right;
            }
            if(smallest != current){
                swap(&heap->data[current], &heap->data[smallest]);
                current = smallest;
            }
            else{
                break;
            }
        }
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int *w = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) scanf("%d", &w[i]);
    
    if(m >= n){
        int max = 0;
        for(int i = 0; i < n; i++) if(w[i] > max) max = w[i];
        printf("%d", max);
        free(w);
        return 0;
    }
    
    MinHeap *heap = initHeap(m);
    int last_time = 0;
    for(int i = 0; i < m; i++){
        heap->data[i] = w[i];
        if(w[i] > last_time) last_time = w[i];
    }
    heap->size = m;
    buildHeap(heap);
    
    int current = m;
    while(current < n){
        int t = heapPop(heap);
        int finish_time = t + w[current];
        heapPush(heap, finish_time);
        if(finish_time > last_time) last_time = finish_time;
        current++;
    }
    
    // After all assignments, find the maximum finish time
    while(heap->size > 0){
        int t = heapPop(heap);
        if(t > last_time) last_time = t;
    }
    
    printf("%d", last_time);
    free(w);
    free(heap->data);
    free(heap);
    return 0;
}