#include <stdio.h>
#include <stdlib.h>

typedef int (*cmp_func)(int a, int b);

typedef struct Heap {
    int* data;
    int size;
    int capacity;
    cmp_func cmp;
} Heap;

int compare_min(int a, int b) {
    return a < b;
}

int compare_max(int a, int b) {
    return a > b;
}

Heap* initHeap(cmp_func cmp) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->capacity = 16;
    heap->size = 0;
    heap->data = (int*)malloc(heap->capacity * sizeof(int));
    heap->cmp = cmp;
    return heap;
}

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void pushHeap(Heap* heap, int val) {
    if (heap->size == heap->capacity) {
        heap->capacity *=2;
        heap->data = (int*)realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->data[heap->size] = val;
    int idx = heap->size;
    heap->size++;
    while (idx > 0) {
        int parent = (idx -1)/2;
        if (heap->cmp(heap->data[idx], heap->data[parent])) {
            swap(&heap->data[idx], &heap->data[parent]);
            idx = parent;
        }
        else break;
    }
}

int popHeap(Heap* heap) {
    if (heap->size ==0) return -1;
    int top = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int idx = 0;
    while (1) {
        int left = 2*idx +1;
        int right = 2*idx +2;
        int target = idx;
        if (left < heap->size && heap->cmp(heap->data[left], heap->data[target])) {
            target = left;
        }
        if (right < heap->size && heap->cmp(heap->data[right], heap->data[target])) {
            target = right;
        }
        if (target != idx) {
            swap(&heap->data[idx], &heap->data[target]);
            idx = target;
        }
        else break;
    }
    return top;
}

int topHeap(Heap* heap) {
    if (heap->size ==0) return -1;
    return heap->data[0];
}

int main(){
    int N;
    scanf("%d", &N);
    int* A = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++) scanf("%d", &A[i]);
    Heap* maxHeap = initHeap(compare_max);
    Heap* minHeap = initHeap(compare_min);
    for(int i=0;i<N;i++){
        if(maxHeap->size ==0 || A[i] <= topHeap(maxHeap)){
            pushHeap(maxHeap, A[i]);
        }
        else{
            pushHeap(minHeap, A[i]);
        }
        if(maxHeap->size > minHeap->size +1){
            int val = popHeap(maxHeap);
            pushHeap(minHeap, val);
        }
        if(minHeap->size > maxHeap->size){
            int val = popHeap(minHeap);
            pushHeap(maxHeap, val);
        }
        if( (i+1) %2 ==1){
            printf("%d\n", topHeap(maxHeap));
        }
    }
    free(A);
    free(maxHeap->data);
    free(maxHeap);
    free(minHeap->data);
    free(minHeap);
    return 0;
}