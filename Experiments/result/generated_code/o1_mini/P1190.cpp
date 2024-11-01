#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity){
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(sizeof(int)*capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int *a, int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

void heapify_up(MinHeap *heap, int idx){
    while(idx > 0){
        int parent = (idx -1)/2;
        if(heap->data[parent] > heap->data[idx]){
            swap(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
        else break;
    }
}

void heapify_down(MinHeap *heap, int idx){
    while(2*idx +1 < heap->size){
        int left = 2*idx +1;
        int right = 2*idx +2;
        int smallest = idx;
        if(left < heap->size && heap->data[left] < heap->data[smallest]){
            smallest = left;
        }
        if(right < heap->size && heap->data[right] < heap->data[smallest]){
            smallest = right;
        }
        if(smallest != idx){
            swap(&heap->data[smallest], &heap->data[idx]);
            idx = smallest;
        }
        else break;
    }
}

void pushHeap(MinHeap *heap, int val){
    if(heap->size == heap->capacity){
        // Should not happen as capacity is m
        return;
    }
    heap->data[heap->size] = val;
    heap->size++;
    heapify_up(heap, heap->size-1);
}

int popHeap(MinHeap *heap){
    if(heap->size ==0){
        return -1;
    }
    int top = heap->data[0];
    heap->data[0] = heap->data[heap->size-1];
    heap->size--;
    heapify_down(heap, 0);
    return top;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int *w = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d", &w[i]);
    MinHeap *heap = createHeap(m);
    int max_time =0;
    for(int i=0;i<m;i++){
        pushHeap(heap, w[i]);
        if(w[i] > max_time) max_time = w[i];
    }
    for(int i=m;i<n;i++){
        int t = popHeap(heap);
        int end_time = t + w[i];
        pushHeap(heap, end_time);
        if(end_time > max_time) max_time = end_time;
    }
    printf("%d\n", max_time);
    free(w);
    free(heap->data);
    free(heap);
    return 0;
}