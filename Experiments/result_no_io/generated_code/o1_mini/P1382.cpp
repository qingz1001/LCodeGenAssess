#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x;
    long long h;
    int type; // 1 for start, -1 for end
} Event;

int cmp(const void *a, const void *b){
    Event *ea = (Event*)a;
    Event *eb = (Event*)b;
    if(ea->x != eb->x)
        return ea->x < eb->x ? -1 : 1;
    if(ea->type != eb->type)
        return ea->type > eb->type ? -1 : 1;
    if(ea->type == 1)
        return ea->h > eb->h ? -1 : 1;
    else
        return ea->h < eb->h ? -1 : 1;
}

typedef struct {
    long long *heap;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createHeap(int capacity){
    MaxHeap *h = (MaxHeap*)malloc(sizeof(MaxHeap));
    h->heap = (long long*)malloc(sizeof(long long)*capacity);
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void swap(long long *a, long long *b){
    long long tmp = *a;
    *a = *b;
    *b = tmp;
}

void push(MaxHeap *h, long long val){
    if(h->size == h->capacity){
        h->capacity *= 2;
        h->heap = (long long*)realloc(h->heap, sizeof(long long)*h->capacity);
    }
    int i = h->size++;
    h->heap[i] = val;
    while(i != 0){
        int parent = (i-1)/2;
        if(h->heap[parent] < h->heap[i]){
            swap(&h->heap[parent], &h->heap[i]);
            i = parent;
        }
        else break;
    }
}

void heapify(MaxHeap *h, int i){
    int largest = i;
    int l = 2*i +1, r = 2*i +2;
    if(l < h->size && h->heap[l] > h->heap[largest])
        largest = l;
    if(r < h->size && h->heap[r] > h->heap[largest])
        largest = r;
    if(largest != i){
        swap(&h->heap[i], &h->heap[largest]);
        heapify(h, largest);
    }
}

long long popMax(MaxHeap *h){
    if(h->size ==0) return 0;
    long long top = h->heap[0];
    h->heap[0] = h->heap[--h->size];
    heapify(h, 0);
    return top;
}

long long peek(MaxHeap *h){
    if(h->size ==0) return 0;
    return h->heap[0];
}

int main(){
    int n;
    scanf("%d", &n);
    Event *events = (Event*)malloc(sizeof(Event)*2*n);
    for(int i=0;i<n;i++){
        long long h, l, r;
        scanf("%lld %lld %lld", &h, &l, &r);
        events[2*i].x = l;
        events[2*i].h = h;
        events[2*i].type = 1;
        events[2*i+1].x = r;
        events[2*i+1].h = h;
        events[2*i+1].type = -1;
    }
    qsort(events, 2*n, sizeof(Event), cmp);
    MaxHeap *heap = createHeap(2*n+2);
    push(heap, 0);
    long long prev = 0;
    // To store the result points
    long long *res_x = (long long*)malloc(sizeof(long long)*(2*n+2));
    long long *res_y = (long long*)malloc(sizeof(long long)*(2*n+2));
    int m =0;
    for(int i=0;i<2*n;i++){
        if(events[i].type ==1){
            push(heap, events[i].h);
        }
        else{
            // Remove one occurrence of events[i].h
            // Marked by lazy removal, since we can't directly remove, so temporarily store
            // Rebuild the heap without one occurrence
            // Not efficient but acceptable for n=1e5
            // So implement a temp heap
            int start =0, end = heap->size;
            long long target = events[i].h;
            for(int j=0;j<heap->size;j++){
                if(heap->heap[j] == target){
                    heap->heap[j] = heap->heap[heap->size-1];
                    heap->size--;
                    heapify(heap, j);
                    break;
                }
            }
        }
        long long current = peek(heap);
        if(current != prev){
            res_x[m] = events[i].x;
            res_y[m] = current;
            m++;
            prev = current;
        }
    }
    // Now, ensure first and last y are 0
    // In the algorithm above, first y should be set when first height changes from 0
    // and last y will be set when height drops to 0
    printf("%d\n", m);
    for(int i=0;i<m;i++){
        printf("%lld %lld\n", res_x[i], res_y[i]);
    }
    free(events);
    free(heap->heap);
    free(heap);
    free(res_x);
    free(res_y);
    return 0;
}