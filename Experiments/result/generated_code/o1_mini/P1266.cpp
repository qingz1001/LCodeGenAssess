#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 150
#define MAXV 500
#define INF 1e18

typedef struct Road {
    int to;
    int V;
    int L;
    struct Road* next;
} Road;

typedef struct {
    double time;
    int node;
    int speed;
} State;

typedef struct {
    State* data;
    int size;
    int capacity;
} Heap;

// Function to initialize the heap
Heap* init_heap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (State*)malloc(sizeof(State) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Function to swap two states
void swap(State* a, State* b) {
    State temp = *a;
    *a = *b;
    *b = temp;
}

// Function to push a state into the heap
void push_heap(Heap* heap, State state) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = (State*)realloc(heap->data, sizeof(State) * heap->capacity);
    }
    heap->data[heap->size] = state;
    int i = heap->size;
    heap->size++;
    // Percolate up
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent].time <= heap->data[i].time)
            break;
        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

// Function to pop the minimum state from the heap
State pop_heap_min(Heap* heap) {
    State min = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    // Percolate down
    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2*i +1;
        int right = 2*i +2;
        if (left < heap->size && heap->data[left].time < heap->data[smallest].time)
            smallest = left;
        if (right < heap->size && heap->data[right].time < heap->data[smallest].time)
            smallest = right;
        if (smallest != i) {
            swap(&heap->data[smallest], &heap->data[i]);
            i = smallest;
        }
        else break;
    }
    return min;
}

// Function to check if heap is empty
int heap_empty(Heap* heap) {
    return heap->size == 0;
}

Road* adj[MAXN];

int main(){
    int N, M, D;
    scanf("%d %d %d", &N, &M, &D);
    // Initialize adjacency list
    for(int i=0;i<N;i++) adj[i] = NULL;
    for(int i=0;i<M;i++){
        int A, B, V, L;
        scanf("%d %d %d %d", &A, &B, &V, &L);
        Road* road = (Road*)malloc(sizeof(Road));
        road->to = B;
        road->V = V;
        road->L = L;
        road->next = adj[A];
        adj[A] = road;
    }
    // Initialize distance and predecessors
    double dist[MAXN][MAXV+1];
    for(int i=0;i<N;i++) {
        for(int j=0;j<=MAXV;j++) dist[i][j] = INF;
    }
    int prev_node_arr[MAXN][MAXV+1];
    int prev_speed_arr[MAXN][MAXV+1];
    for(int i=0;i<N;i++) {
        for(int j=0;j<=MAXV;j++) {
            prev_node_arr[i][j] = -1;
            prev_speed_arr[i][j] = -1;
        }
    }
    // Initialize heap
    Heap* heap = init_heap(75000);
    State start;
    start.time = 0.0;
    start.node = 0;
    start.speed = 70;
    push_heap(heap, start);
    dist[0][70] = 0.0;
    // Dijkstra's algorithm
    while(!heap_empty(heap)){
        State current = pop_heap_min(heap);
        int u = current.node;
        int s = current.speed;
        double t = current.time;
        if(u == D){
            break;
        }
        if(t > dist[u][s]) continue;
        Road* ptr = adj[u];
        while(ptr){
            int v = ptr->to;
            int V = ptr->V;
            int L = ptr->L;
            double new_time;
            int new_speed;
            if(V != 0){
                new_time = t + ((double)L) / V;
                new_speed = V;
            }
            else{
                new_time = t + ((double)L) / s;
                new_speed = s;
            }
            if(new_speed > MAXV) new_speed = MAXV;
            if(new_speed <0) new_speed =0;
            if(new_time < dist[v][new_speed]){
                dist[v][new_speed] = new_time;
                prev_node_arr[v][new_speed] = u;
                prev_speed_arr[v][new_speed] = s;
                State new_state;
                new_state.time = new_time;
                new_state.node = v;
                new_state.speed = new_speed;
                push_heap(heap, new_state);
            }
            ptr = ptr->next;
        }
    }
    // Find the speed at D with minimal time
    double min_time = INF;
    int final_speed = -1;
    for(int s=0;s<=MAXV;s++) {
        if(dist[D][s] < min_time){
            min_time = dist[D][s];
            final_speed = s;
        }
    }
    // Reconstruct the path
    int path[1000];
    int path_len =0;
    int current_node = D;
    int current_speed = final_speed;
    while(current_node != -1){
        path[path_len++] = current_node;
        int prev = prev_node_arr[current_node][current_speed];
        if(prev == -1) break;
        int prev_s = prev_speed_arr[current_node][current_speed];
        current_node = prev;
        current_speed = prev_s;
    }
    // Reverse the path
    for(int i=path_len-1;i>=0;i--){
        printf("%d", path[i]);
        if(i!=0) printf(" ");
    }
    // Free memory
    for(int i=0;i<N;i++){
        Road* ptr = adj[i];
        while(ptr){
            Road* tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }
    free(heap->data);
    free(heap);
    return 0;
}