#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define INF 1000000000000000000ULL

typedef struct {
    int to;
    int w;
} Edge;

typedef struct {
    Edge *edges;
    int *offset;
} Graph;

typedef struct {
    int size;
    int capacity;
    int *heap;
    uint64_t *dist;
} PriorityQueue;

// Function to create a graph
Graph create_graph(int n, int m) {
    Graph g;
    g.edges = (Edge*)malloc(sizeof(Edge) * m);
    g.offset = (int*)calloc(n + 1, sizeof(int));
    return g;
}

// Function to add edges to the graph
void add_edges(Graph *g, int m, Edge *temp_edges) {
    for(int i = 0; i < m; i++) {
        g->edges[i].to = temp_edges[i].to;
        g->edges[i].w = temp_edges[i].w;
    }
}

// Function to build adjacency list
void build_adjacency(Graph *g, int n, int m) {
    int *count = (int*)calloc(n, sizeof(int));
    for(int i = 0; i < m; i++) {
        count[g->edges[i].to]++;
    }
    g->offset[0] = 0;
    for(int i = 1; i <= n; i++) {
        g->offset[i] = g->offset[i-1] + count[i-1];
    }
    int *current = (int*)calloc(n, sizeof(int));
    Edge *sorted = (Edge*)malloc(sizeof(Edge) * m);
    for(int i = 0; i < m; i++) {
        int u = g->edges[i].to;
        int pos = g->offset[u] + current[u]++;
        sorted[pos].to = g->edges[i].to;
        sorted[pos].w = g->edges[i].w;
    }
    free(g->edges);
    g->edges = sorted;
    free(count);
    free(current);
}

// Function to initialize priority queue
PriorityQueue* init_pq(int n) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->size = 0;
    pq->capacity = n;
    pq->heap = (int*)malloc(sizeof(int) * n);
    pq->dist = (uint64_t*)malloc(sizeof(uint64_t) * n);
    return pq;
}

// Swap function
void swap(int *a, int *b, uint64_t *dist) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Push to priority queue
void push_pq(PriorityQueue *pq, int node, uint64_t distance) {
    pq->heap[pq->size] = node;
    pq->dist[node] = distance;
    int i = pq->size;
    pq->size++;
    while(i > 0){
        int parent = (i - 1) / 2;
        if(pq->dist[pq->heap[parent]] <= pq->dist[pq->heap[i]]) break;
        swap(&pq->heap[parent], &pq->heap[i], pq->dist);
        i = parent;
    }
}

// Pop from priority queue
int pop_pq(PriorityQueue *pq) {
    if(pq->size == 0) return -1;
    int top = pq->heap[0];
    pq->size--;
    pq->heap[0] = pq->heap[pq->size];
    int i = 0;
    while(1){
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;
        if(left < pq->size && pq->dist[pq->heap[left]] < pq->dist[pq->heap[smallest]]) smallest = left;
        if(right < pq->size && pq->dist[pq->heap[right]] < pq->dist[pq->heap[smallest]]) smallest = right;
        if(smallest != i){
            swap(&pq->heap[smallest], &pq->heap[i], pq->dist);
            i = smallest;
        }
        else break;
    }
    return top;
}

// Dijkstra's algorithm
uint64_t* dijkstra(Graph *g, int n, int start) {
    uint64_t *dist = (uint64_t*)malloc(sizeof(uint64_t) * n);
    for(int i = 0; i < n; i++) dist[i] = INF;
    dist[start] = 0;
    PriorityQueue *pq = init_pq(n);
    push_pq(pq, start, 0);
    while(pq->size > 0){
        int u = pop_pq(pq);
        if(u == -1) break;
        for(int i = g->offset[u]; i < g->offset[u+1]; i++){
            int v = g->edges[i].to;
            uint64_t w = g->edges[i].w;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                push_pq(pq, v, dist[v]);
            }
        }
    }
    free(pq->heap);
    free(pq->dist);
    free(pq);
    return dist;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Temporary storage for edges
    Edge *forward_temp = (Edge*)malloc(sizeof(Edge) * m);
    Edge *reverse_temp = (Edge*)malloc(sizeof(Edge) * m);
    
    for(int i = 0; i < m; i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        forward_temp[i].to = v-1;
        forward_temp[i].w = w;
        reverse_temp[i].to = u-1;
        reverse_temp[i].w = w;
    }
    
    // Create forward graph
    Graph forward = create_graph(n, m);
    forward.edges = forward_temp;
    build_adjacency(&forward, n, m);
    
    // Create reverse graph
    Graph reverse = create_graph(n, m);
    reverse.edges = reverse_temp;
    build_adjacency(&reverse, n, m);
    
    // Compute shortest paths from 0 in forward graph
    uint64_t *dist_forward = dijkstra(&forward, n, 0);
    
    // Compute shortest paths from 0 in reverse graph
    uint64_t *dist_reverse = dijkstra(&reverse, n, 0);
    
    uint64_t total = 0;
    for(int i = 0; i < n; i++) {
        total += dist_forward[i] + dist_reverse[i];
    }
    
    printf("%llu\n", total);
    
    // Free memory
    free(forward.edges);
    free(forward.offset);
    free(reverse.edges);
    free(reverse.offset);
    free(dist_forward);
    free(dist_reverse);
    free(forward_temp);
    free(reverse_temp);
    
    return 0;
}