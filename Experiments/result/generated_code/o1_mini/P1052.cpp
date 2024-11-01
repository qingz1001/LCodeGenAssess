#include <stdio.h>
#include <stdlib.h>

#define INF 1000000
#define MAX_M 102

typedef struct {
    int cost;
    int index;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode)*capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode* a, HeapNode* b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void pushHeap(MinHeap* heap, HeapNode node){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode)*heap->capacity);
    }
    heap->data[heap->size] = node;
    int i = heap->size;
    heap->size++;
    while(i>0){
        int parent = (i-1)/2;
        if(heap->data[parent].cost <= heap->data[i].cost) break;
        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

HeapNode popHeap(MinHeap* heap){
    HeapNode top = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int i =0;
    while(1){
        int left = 2*i+1;
        int right = 2*i+2;
        int smallest = i;
        if(left < heap->size && heap->data[left].cost < heap->data[smallest].cost)
            smallest = left;
        if(right < heap->size && heap->data[right].cost < heap->data[smallest].cost)
            smallest = right;
        if(smallest != i){
            swap(&heap->data[smallest], &heap->data[i]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int compare(const void* a, const void* b){
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int L;
    scanf("%d", &L);
    int S, T, M;
    scanf("%d %d %d", &S, &T, &M);
    int stones[MAX_M];
    for(int i=0;i<M;i++) scanf("%d", &stones[i]);
    qsort(stones, M, sizeof(int), compare);
    int pos[MAX_M+2];
    pos[0] = 0;
    for(int i=1;i<=M;i++) pos[i] = stones[i-1];
    pos[M+1] = L;
    int isStone[MAX_M+2];
    isStone[0] = 0;
    for(int i=1;i<=M;i++) isStone[i] = 1;
    isStone[M+1] = 0;
    int size = M+2;
    int dist[MAX_M+2];
    for(int i=0;i<size;i++) dist[i] = INF;
    dist[0] = 0;
    MinHeap* heap = createHeap(256);
    HeapNode start;
    start.cost = 0;
    start.index = 0;
    pushHeap(heap, start);
    while(heap->size >0){
        HeapNode current = popHeap(heap);
        if(current.index == size-1) break;
        if(current.cost > dist[current.index]) continue;
        for(int s=S;s<=T;s++){
            int target = pos[current.index] + s;
            if(target >= L){
                if(dist[size-1] > current.cost){
                    dist[size-1] = current.cost;
                    HeapNode node;
                    node.cost = dist[size-1];
                    node.index = size-1;
                    pushHeap(heap, node);
                }
                continue;
            }
            // Binary search
            int left = current.index +1, right = size-2, mid, found = -1;
            while(left <= right){
                mid = (left + right)/2;
                if(pos[mid] == target){
                    found = mid;
                    break;
                }
                else if(pos[mid] < target) left = mid +1;
                else right = mid -1;
            }
            if(found != -1){
                int new_cost = current.cost + isStone[found];
                if(new_cost < dist[found]){
                    dist[found] = new_cost;
                    HeapNode node;
                    node.cost = dist[found];
                    node.index = found;
                    pushHeap(heap, node);
                }
            }
        }
    }
    printf("%d\n", dist[size-1]);
    free(heap->data);
    free(heap);
    return 0;
}