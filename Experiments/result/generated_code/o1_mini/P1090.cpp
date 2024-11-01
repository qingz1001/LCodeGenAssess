#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

// Initialize the heap
MinHeap* initHeap(int capacity){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(sizeof(int)*(capacity+1));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Swap two elements
void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Heapify up
void heapify_up(MinHeap* heap, int idx){
    while(idx >1){
        int parent = idx /2;
        if(heap->data[parent] > heap->data[idx]){
            swap(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
        else{
            break;
        }
    }
}

// Heapify down
void heapify_down(MinHeap* heap, int idx){
    while(2*idx <= heap->size){
        int smallest = idx;
        int left = 2*idx;
        int right = 2*idx +1;
        if(left <= heap->size && heap->data[left] < heap->data[smallest]){
            smallest = left;
        }
        if(right <= heap->size && heap->data[right] < heap->data[smallest]){
            smallest = right;
        }
        if(smallest != idx){
            swap(&heap->data[smallest], &heap->data[idx]);
            idx = smallest;
        }
        else{
            break;
        }
    }
}

// Insert into heap
void insertHeap(MinHeap* heap, int value){
    if(heap->size +1 > heap->capacity){
        // Normally, resize. But n<=10000, no need.
        return;
    }
    heap->data[++heap->size] = value;
    heapify_up(heap, heap->size);
}

// Extract min from heap
int extractMin(MinHeap* heap){
    if(heap->size <1){
        return -1; // Should not happen
    }
    int min = heap->data[1];
    heap->data[1] = heap->data[heap->size--];
    heapify_down(heap,1);
    return min;
}

int main(){
    int n;
    if(scanf("%d", &n)!=1){
        return 0;
    }
    MinHeap* heap = initHeap(n);
    for(int i=0;i<n;i++){
        int a;
        scanf("%d", &a);
        insertHeap(heap, a);
    }
    if(n ==1){
        printf("0\n");
        free(heap->data);
        free(heap);
        return 0;
    }
    ll total_cost =0;
    while(heap->size >1){
        int first = extractMin(heap);
        int second = extractMin(heap);
        ll sum = (ll)first + (ll)second;
        total_cost += sum;
        insertHeap(heap, (int)sum);
    }
    printf("%lld\n", total_cost);
    free(heap->data);
    free(heap);
    return 0;
}