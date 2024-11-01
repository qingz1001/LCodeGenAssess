#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 150
#define MAX_M 150
#define MAX_V 500
#define INF 1e18

typedef struct Road {
    int to;
    int V;
    int L;
} Road;

typedef struct State {
    int node;
    int speed;
    double time;
} State;

typedef struct Heap {
    State *data;
    int size;
    int capacity;
} Heap;

// Heap functions
Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (State*)malloc(sizeof(State) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(State* a, State* b) {
    State temp = *a;
    *a = *b;
    *b = temp;
}

void pushHeap(Heap* heap, State s) {
    if (heap->size >= heap->capacity) return;
    heap->data[heap->size] = s;
    int i = heap->size;
    heap->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent].time > heap->data[i].time) {
            swap(&heap->data[parent], &heap->data[i]);
            i = parent;
        }
        else break;
    }
}

State popHeap(Heap* heap) {
    State top = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int i = 0;
    while (1) {
        int left = 2*i +1;
        int right = 2*i +2;
        int smallest = i;
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
    return top;
}

int isEmpty(Heap* heap) {
    return heap->size == 0;
}

int main(){
    int N, M, D;
    scanf("%d %d %d", &N, &M, &D);
    Road adj[MAX_N][MAX_M];
    int adj_size[MAX_N];
    for(int i=0;i<N;i++) adj_size[i]=0;
    for(int i=0;i<M;i++){
        int A, B, V, L;
        scanf("%d %d %d %d", &A, &B, &V, &L);
        adj[A][adj_size[A]].to = B;
        adj[A][adj_size[A]].V = V;
        adj[A][adj_size[A]].L = L;
        adj_size[A]++;
    }
    double time_arr[MAX_N][MAX_V+1];
    for(int i=0;i<N;i++) {
        for(int j=0;j<=MAX_V;j++) {
            time_arr[i][j] = INF;
        }
    }
    int pre_node[MAX_N][MAX_V+1];
    int pre_speed[MAX_N][MAX_V+1];
    for(int i=0;i<N;i++) {
        for(int j=0;j<=MAX_V;j++) {
            pre_node[i][j] = -1;
            pre_speed[i][j] = -1;
        }
    }
    time_arr[0][70] = 0.0;
    Heap* heap = createHeap(MAX_N * (MAX_V+1));
    State start;
    start.node = 0;
    start.speed = 70;
    start.time = 0.0;
    pushHeap(heap, start);
    while(!isEmpty(heap)){
        State current = popHeap(heap);
        int u = current.node;
        int s = current.speed;
        double t = current.time;
        if(u == D){
            break;
        }
        if(t > time_arr[u][s]){
            continue;
        }
        for(int i=0;i<adj_size[u];i++){
            Road road = adj[u][i];
            int v = road.to;
            int V = road.V;
            int L = road.L;
            int new_speed;
            double new_time;
            if(V == 0){
                if(s == 0) continue;
                new_speed = s;
                new_time = t + ((double)L) / s;
            }
            else{
                new_speed = V;
                new_time = t + ((double)L) / V;
            }
            if(new_speed > MAX_V) continue;
            if(new_time + 1e-9 < time_arr[v][new_speed]){
                time_arr[v][new_speed] = new_time;
                pre_node[v][new_speed] = u;
                pre_speed[v][new_speed] = s;
                State next;
                next.node = v;
                next.speed = new_speed;
                next.time = new_time;
                pushHeap(heap, next);
            }
        }
    }
    // Find minimum time to D
    double min_time = INF;
    int final_speed = -1;
    for(int s=0;s<=MAX_V;s++){
        if(time_arr[D][s] < min_time){
            min_time = time_arr[D][s];
            final_speed = s;
        }
    }
    // Reconstruct path
    int path[MAX_N];
    int path_size = 0;
    int current_node = D;
    int current_speed = final_speed;
    while(current_node != -1){
        path[path_size++] = current_node;
        int prev = pre_node[current_node][current_speed];
        if(prev == -1) break;
        int prev_s = pre_speed[current_node][current_speed];
        current_node = prev;
        current_speed = prev_s;
    }
    // Print path in reverse
    for(int i=path_size-1;i>=0;i--){
        printf("%d", path[i]);
        if(i !=0) printf(" ");
    }
    printf("\n");
    // Free heap
    free(heap->data);
    free(heap);
    return 0;
}