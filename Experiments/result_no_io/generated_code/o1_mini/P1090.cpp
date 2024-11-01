#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(sizeof(int)*(capacity+1));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int *a, int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

void heapifyUp(MinHeap* heap, int index){
    while(index >1){
        int parent = index/2;
        if(heap->data[parent] > heap->data[index]){
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        }
        else break;
    }
}

void heapifyDown(MinHeap* heap, int index){
    while(2*index <= heap->size){
        int smallest = index;
        int left = 2*index;
        int right = 2*index+1;
        if(left <= heap->size && heap->data[left] < heap->data[smallest]){
            smallest = left;
        }
        if(right <= heap->size && heap->data[right] < heap->data[smallest]){
            smallest = right;
        }
        if(smallest != index){
            swap(&heap->data[smallest], &heap->data[index]);
            index = smallest;
        }
        else break;
    }
}

void insertHeap(MinHeap* heap, int val){
    if(heap->size >= heap->capacity){
        // Resize
        heap->capacity *=2;
        heap->data = (int*)realloc(heap->data, sizeof(int)*(heap->capacity+1));
    }
    heap->size++;
    heap->data[heap->size] = val;
    heapifyUp(heap, heap->size);
}

int extractMin(MinHeap* heap){
    if(heap->size <1) return -1;
    int min = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    heapifyDown(heap,1);
    return min;
}

int main(){
    int n;
    scanf("%d", &n);
    MinHeap* heap = createHeap(n);
    for(int i=0;i<n;i++){
        int x;
        scanf("%d", &x);
        insertHeap(heap, x);
    }
    long long total=0;
    while(heap->size >1){
        int a = extractMin(heap);
        int b = extractMin(heap);
        long long sum = (long long)a + (long long)b;
        total += sum;
        insertHeap(heap, sum);
    }
    printf("%lld\n", total);
    free(heap->data);
    free(heap);
    return 0;
}