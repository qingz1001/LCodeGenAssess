#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long data[200005];
    int size;
} MaxHeap;

typedef struct {
    long long data[200005];
    int size;
} MinHeap;

void maxHeap_push(MaxHeap *heap, long long val) {
    int i = ++heap->size;
    heap->data[i] = val;
    while(i > 1 && heap->data[i] > heap->data[i/2]){
        long long temp = heap->data[i];
        heap->data[i] = heap->data[i/2];
        heap->data[i/2] = temp;
        i /= 2;
    }
}

long long maxHeap_pop(MaxHeap *heap){
    if(heap->size == 0) return 0;
    long long top = heap->data[1];
    heap->data[1] = heap->data[heap->size--];
    int i =1;
    while(1){
        int largest = i;
        int left = 2*i;
        int right = 2*i+1;
        if(left <= heap->size && heap->data[left] > heap->data[largest]) largest = left;
        if(right <= heap->size && heap->data[right] > heap->data[largest]) largest = right;
        if(largest != i){
            long long temp = heap->data[i];
            heap->data[i] = heap->data[largest];
            heap->data[largest] = temp;
            i = largest;
        }
        else break;
    }
    return top;
}

long long maxHeap_top(MaxHeap *heap){
    if(heap->size == 0) return 0;
    return heap->data[1];
}

void minHeap_push(MinHeap *heap, long long val) {
    int i = ++heap->size;
    heap->data[i] = val;
    while(i > 1 && heap->data[i] < heap->data[i/2]){
        long long temp = heap->data[i];
        heap->data[i] = heap->data[i/2];
        heap->data[i/2] = temp;
        i /= 2;
    }
}

long long minHeap_pop(MinHeap *heap){
    if(heap->size == 0) return 0;
    long long top = heap->data[1];
    heap->data[1] = heap->data[heap->size--];
    int i =1;
    while(1){
        int smallest = i;
        int left = 2*i;
        int right = 2*i+1;
        if(left <= heap->size && heap->data[left] < heap->data[smallest]) smallest = left;
        if(right <= heap->size && heap->data[right] < heap->data[smallest]) smallest = right;
        if(smallest != i){
            long long temp = heap->data[i];
            heap->data[i] = heap->data[smallest];
            heap->data[smallest] = temp;
            i = smallest;
        }
        else break;
    }
    return top;
}

long long minHeap_top(MinHeap *heap){
    if(heap->size == 0) return 0;
    return heap->data[1];
}

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    long long *a = (long long*)malloc((m+1)*sizeof(long long));
    for(int i=1;i<=m;i++) scanf("%lld", &a[i]);
    int *u = (int*)malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &u[i]);
    MaxHeap maxH;
    maxH.size =0;
    MinHeap minH;
    minH.size =0;
    int i_val=0, j=0;
    for(int k=1;k<=n;k++){
        int target = u[k];
        while(j < target){
            j++;
            long long x = a[j];
            if(maxH.size < i_val +1){
                maxHeap_push(&maxH, x);
            }
            else{
                if(x < maxHeap_top(&maxH)){
                    maxHeap_push(&maxH, x);
                    long long y = maxHeap_pop(&maxH);
                    minHeap_push(&minH, y);
                }
                else{
                    minHeap_push(&minH, x);
                }
            }
        }
        i_val++;
        while(maxH.size > i_val){
            long long y = maxHeap_pop(&maxH);
            minHeap_push(&minH, y);
        }
        while(maxH.size < i_val && minH.size >0){
            long long y = minHeap_pop(&minH);
            maxHeap_push(&maxH, y);
        }
        printf("%lld\n", maxHeap_top(&maxH));
    }
    free(a);
    free(u);
    return 0;
}