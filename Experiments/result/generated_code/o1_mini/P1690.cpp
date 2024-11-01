#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_P 10
#define MAX_MASK (1<<MAX_P)
#define INF 1000000000

typedef struct {
    int node;
    int mask;
    int dist;
} State;

typedef struct {
    State *data;
    int size;
    int capacity;
} MinHeap;

// Initialize the heap
void initHeap(MinHeap *heap, int capacity){
    heap->data = (State*)malloc(sizeof(State) * (capacity + 1));
    heap->size = 0;
    heap->capacity = capacity;
}

// Swap two states
void swap(State *a, State *b){
    State temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up
void heapifyUp(MinHeap *heap, int idx){
    while(idx > 1){
        int parent = idx / 2;
        if(heap->data[parent].dist > heap->data[idx].dist){
            swap(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
        else{
            break;
        }
    }
}

// Heapify down
void heapifyDown(MinHeap *heap, int idx){
    while(2*idx <= heap->size){
        int smallest = idx;
        int left = 2*idx;
        int right = 2*idx +1;
        if(left <= heap->size && heap->data[left].dist < heap->data[smallest].dist){
            smallest = left;
        }
        if(right <= heap->size && heap->data[right].dist < heap->data[smallest].dist){
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

// Push to heap
void pushHeap(MinHeap *heap, State s){
    if(heap->size +1 > heap->capacity){
        heap->capacity *=2;
        heap->data = (State*)realloc(heap->data, sizeof(State)*(heap->capacity +1));
    }
    heap->size++;
    heap->data[heap->size] = s;
    heapifyUp(heap, heap->size);
}

// Pop from heap
State popHeap(MinHeap *heap){
    State top = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    heapifyDown(heap, 1);
    return top;
}

// Check if heap is empty
int isEmpty(MinHeap *heap){
    return heap->size ==0;
}

int main(){
    int N;
    scanf("%d", &N);
    int distance_matrix[MAX_N+1][MAX_N+1];
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            scanf("%d", &distance_matrix[i][j]);
        }
    }
    int P;
    scanf("%d", &P);
    int treasures[MAX_P];
    for(int i=0;i<P;i++) scanf("%d", &treasures[i]);
    int treasure_bit[MAX_N+1];
    for(int i=1;i<=N;i++) treasure_bit[i] = -1;
    for(int i=0;i<P;i++) treasure_bit[treasures[i]] = i;
    int initial_mask =0;
    if(treasure_bit[1] != -1){
        initial_mask |= (1 << treasure_bit[1]);
    }
    int goal_mask = (P ==0) ? 0 : ((1<<P)-1);
    // Initialize distance array
    int dist_array[MAX_N+1][MAX_MASK];
    for(int i=1;i<=N;i++) {
        for(int m=0;m<(1<<P);m++) {
            dist_array[i][m] = INF;
        }
    }
    dist_array[1][initial_mask] =0;
    // Initialize heap
    MinHeap heap;
    initHeap(&heap, 102400);
    State start;
    start.node =1;
    start.mask = initial_mask;
    start.dist =0;
    pushHeap(&heap, start);
    while(!isEmpty(&heap)){
        State current = popHeap(&heap);
        if(current.node == N && current.mask == goal_mask){
            printf("%d", current.dist);
            return 0;
        }
        if(current.dist > dist_array[current.node][current.mask]){
            continue;
        }
        for(int v=1; v<=N; v++){
            if(distance_matrix[current.node][v] <0) continue;
            int new_dist = current.dist + distance_matrix[current.node][v];
            int new_mask = current.mask;
            if(treasure_bit[v] != -1){
                new_mask |= (1 << treasure_bit[v]);
            }
            if(new_dist < dist_array[v][new_mask]){
                dist_array[v][new_mask] = new_dist;
                State next;
                next.node =v;
                next.mask = new_mask;
                next.dist = new_dist;
                pushHeap(&heap, next);
            }
        }
    }
    return 0;
}