#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (ll*)malloc(sizeof(ll) * (capacity + 1));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(ll *a, ll *b){
    ll temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap* heap, int idx){
    while(idx > 1){
        int parent = idx / 2;
        if(heap->data[parent] <= heap->data[idx]) break;
        swap(&heap->data[parent], &heap->data[idx]);
        idx = parent;
    }
}

void heapifyDown(MinHeap* heap, int idx){
    while(2 * idx <= heap->size){
        int smallest = idx;
        int left = 2 * idx;
        int right = 2 * idx + 1;
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

void pushHeap(MinHeap* heap, ll val){
    if(heap->size +1 > heap->capacity){
        heap->capacity *=2;
        heap->data = (ll*)realloc(heap->data, sizeof(ll)*(heap->capacity +1));
    }
    heap->size++;
    heap->data[heap->size] = val;
    heapifyUp(heap, heap->size);
}

ll popHeap(MinHeap* heap){
    if(heap->size ==0) return -1;
    ll top = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    heapifyDown(heap,1);
    return top;
}

ll simulate(int K, ll d[], int N){
    MinHeap* heap = createHeap(K >0 ? K :1);
    ll T = 0;
    for(int i=0;i<K && i<N;i++){
        pushHeap(heap, d[i]);
        if(d[i] > T) T = d[i];
    }
    for(int i=K;i<N;i++){
        ll current = popHeap(heap);
        ll finish_time = current + d[i];
        pushHeap(heap, finish_time);
        if(finish_time > T) T = finish_time;
    }
    // Now pop all remaining finish times to find the max
    while(heap->size >0){
        ll current = popHeap(heap);
        if(current > T) T = current;
    }
    free(heap->data);
    free(heap);
    return T;
}

int main(){
    int N;
    ll T_max;
    scanf("%d %lld", &N, &T_max);
    ll *d = (ll*)malloc(sizeof(ll)*N);
    for(int i=0;i<N;i++) scanf("%lld", &d[i]);
    int left =1, right = N, answer = N;
    while(left <= right){
        int mid = left + (right - left)/2;
        ll T = simulate(mid, d, N);
        if(T <= T_max){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%d\n", answer);
    free(d);
    return 0;
}