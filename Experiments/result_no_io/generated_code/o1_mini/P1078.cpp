#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_N 101
#define MAX_K 100
#define MAX_M 10000
#define INF 1000000000

typedef struct Edge {
    int to;
    int cost;
    struct Edge* next;
} Edge;

typedef struct {
    Edge* head;
} Graph;

typedef struct State {
    int country;
    uint64_t mask_low;
    uint64_t mask_high;
    int dist;
} State;

typedef struct {
    State* data;
    int size;
    int capacity;
} PriorityQueue;

void initQueue(PriorityQueue* pq) {
    pq->capacity = 1000000;
    pq->size = 0;
    pq->data = (State*)malloc(sizeof(State) * pq->capacity);
}

void swap(State* a, State* b) {
    State temp = *a;
    *a = *b;
    *b = temp;
}

void pushQueue(PriorityQueue* pq, State state) {
    if (pq->size >= pq->capacity) return;
    pq->data[pq->size] = state;
    int i = pq->size;
    pq->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (pq->data[parent].dist <= pq->data[i].dist) break;
        swap(&pq->data[parent], &pq->data[i]);
        i = parent;
    }
}

State popQueue(PriorityQueue* pq) {
    State top = pq->data[0];
    pq->size--;
    pq->data[0] = pq->data[pq->size];
    int i = 0;
    while (1) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;
        if (left < pq->size && pq->data[left].dist < pq->data[smallest].dist)
            smallest = left;
        if (right < pq->size && pq->data[right].dist < pq->data[smallest].dist)
            smallest = right;
        if (smallest == i) break;
        swap(&pq->data[i], &pq->data[smallest]);
        i = smallest;
    }
    return top;
}

int is_visited(int country, uint64_t mask_low, uint64_t mask_high, uint64_t visited_low[], uint64_t visited_high[]) {
    return (visited_low[country] & mask_low) && (visited_high[country] & mask_high);
}

void set_visited(int country, uint64_t mask_low, uint64_t mask_high, uint64_t visited_low[], uint64_t visited_high[]) {
    visited_low[country] |= mask_low;
    visited_high[country] |= mask_high;
}

int main(){
    int N, K, M, S, T;
    scanf("%d %d %d %d %d", &N, &K, &M, &S, &T);
    
    int C[MAX_N];
    for(int i=1;i<=N;i++) scanf("%d", &C[i]);
    
    int a[MAX_K+1][MAX_K+1];
    for(int i=1;i<=K;i++) {
        for(int j=1;j<=K;j++) scanf("%d", &a[i][j]);
    }
    
    Graph graph[MAX_N];
    for(int i=1;i<=N;i++) graph[i].head = NULL;
    for(int i=0;i<M;i++){
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        Edge* e1 = (Edge*)malloc(sizeof(Edge));
        e1->to = v;
        e1->cost = d;
        e1->next = graph[u].head;
        graph[u].head = e1;
        Edge* e2 = (Edge*)malloc(sizeof(Edge));
        e2->to = u;
        e2->cost = d;
        e2->next = graph[v].head;
        graph[v].head = e2;
    }
    
    PriorityQueue pq;
    initQueue(&pq);
    
    State start;
    start.country = S;
    start.mask_low = 0;
    start.mask_high = 0;
    if(C[S] <= 64) {
        start.mask_low |= (1ULL << (C[S]-1));
    }
    else {
        start.mask_high |= (1ULL << (C[S]-1 - 64));
    }
    start.dist = 0;
    pushQueue(&pq, start);
    
    uint64_t visited_low[MAX_N];
    uint64_t visited_high_arr[MAX_N];
    for(int i=1;i<=N;i++) { visited_low[i]=0; visited_high_arr[i]=0; }
    set_visited(S, start.mask_low, start.mask_high, visited_low, visited_high_arr);
    
    int answer = -1;
    
    while(pq.size > 0){
        State current = popQueue(&pq);
        if(current.country == T){
            answer = current.dist;
            break;
        }
        Edge* edge = graph[current.country].head;
        while(edge){
            int next = edge->to;
            int culture = C[next];
            uint64_t new_mask_low = current.mask_low;
            uint64_t new_mask_high = current.mask_high;
            if(culture <= 64){
                if((current.mask_low & (1ULL << (culture-1))) ) {
                    edge = edge->next;
                    continue;
                }
                new_mask_low |= (1ULL << (culture-1));
            }
            else{
                if((current.mask_high & (1ULL << (culture-1 - 64))) ) {
                    edge = edge->next;
                    continue;
                }
                new_mask_high |= (1ULL << (culture-1 - 64));
            }
            // Check exclusions
            int conflict = 0;
            for(int c=1;c<=K;c++){
                if(c <= 64){
                    if(new_mask_low & (1ULL << (c-1))){
                        for(int j=1;j<=K;j++) {
                            if(a[c][j]){
                                if(j <= 64){
                                    if(new_mask_low & (1ULL << (j-1))){
                                        conflict = 1;
                                        break;
                                    }
                                }
                                else{
                                    if(new_mask_high & (1ULL << (j-1 - 64))){
                                        conflict = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                else{
                    if(new_mask_high & (1ULL << (c-1 - 64))){
                        for(int j=1;j<=K;j++) {
                            if(a[c][j]){
                                if(j <= 64){
                                    if(new_mask_low & (1ULL << (j-1))){
                                        conflict = 1;
                                        break;
                                    }
                                }
                                else{
                                    if(new_mask_high & (1ULL << (j-1 - 64))){
                                        conflict = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                if(conflict) break;
            }
            if(conflict){
                edge = edge->next;
                continue;
            }
            // Check if visited
            if(is_visited(next, new_mask_low, new_mask_high, visited_low, visited_high_arr)){
                edge = edge->next;
                continue;
            }
            // Mark visited
            set_visited(next, new_mask_low, new_mask_high, visited_low, visited_high_arr);
            // Push to queue
            State next_state;
            next_state.country = next;
            next_state.mask_low = new_mask_low;
            next_state.mask_high = new_mask_high;
            next_state.dist = current.dist + edge->cost;
            pushQueue(&pq, next_state);
            edge = edge->next;
        }
    }
    
    printf("%d\n", answer);
    
    // Free memory
    for(int i=1;i<=N;i++){
        Edge* e = graph[i].head;
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(pq.data);
    
    return 0;
}