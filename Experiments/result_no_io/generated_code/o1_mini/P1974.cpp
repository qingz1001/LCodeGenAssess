#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity){
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (ll*)malloc(sizeof(ll) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(ll *a, ll *b){
    ll temp = *a;
    *a = *b;
    *b = temp;
}

void pushHeap(MinHeap *heap, ll val){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (ll*)realloc(heap->data, sizeof(ll)*heap->capacity);
    }
    heap->data[heap->size] = val;
    int i = heap->size;
    heap->size++;
    while(i > 0){
        int parent = (i -1)/2;
        if(heap->data[parent] > heap->data[i]){
            swap(&heap->data[parent], &heap->data[i]);
            i = parent;
        }
        else break;
    }
}

ll popHeap(MinHeap *heap){
    if(heap->size ==0) return -1;
    ll min = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int i =0;
    while(1){
        int left = 2*i +1;
        int right = 2*i +2;
        int smallest = i;
        if(left < heap->size && heap->data[left] < heap->data[smallest]) smallest = left;
        if(right < heap->size && heap->data[right] < heap->data[smallest]) smallest = right;
        if(smallest != i){
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return min;
}

int main(){
    int n;
    scanf("%d", &n);
    MinHeap *heap = createHeap(n > 0 ? n : 1);
    for(int i=0;i<n;i++) pushHeap(heap, 1LL);
    while(heap->size >1){
        ll A = popHeap(heap);
        ll B = popHeap(heap);
        ll C = 1 + A * B;
        pushHeap(heap, C);
    }
    if(heap->size ==1){
        printf("%lld\n", heap->data[0]);
    }
    else{
        printf("0\n");
    }
    free(heap->data);
    free(heap);
    return 0;
}