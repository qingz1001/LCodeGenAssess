#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 30001
#define MAX_M 600000
#define MAX_K 11
#define INF 1000000000

typedef struct {
    int v;
    int dist;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

// Initialize the heap
void initHeap(MinHeap *heap, int capacity) {
    heap->data = (HeapNode *)malloc(sizeof(HeapNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
}

// Swap two heap nodes
void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Push a node into the heap
void pushHeap(MinHeap *heap, int v, int dist) {
    if (heap->size >= heap->capacity) return;
    heap->data[heap->size].v = v;
    heap->data[heap->size].dist = dist;
    int i = heap->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent].dist <= heap->data[i].dist) break;
        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

// Pop the smallest node from the heap
HeapNode popHeap(MinHeap *heap) {
    HeapNode top = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2*i +1;
        int right = 2*i +2;
        if (left < heap->size && heap->data[left].dist < heap->data[smallest].dist)
            smallest = left;
        if (right < heap->size && heap->data[right].dist < heap->data[smallest].dist)
            smallest = right;
        if (smallest != i) {
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

// Free the heap
void freeHeap(MinHeap *heap) {
    free(heap->data);
}

// Edge representation
typedef struct {
    int to;
    int t;
    int next;
} EdgeStruct;

EdgeStruct edges[MAX_M];
int adj_head_arr[MAX_N];
int edge_cnt = 0;

// Add edge to adjacency list
void addEdge(int a, int b, int t) {
    edges[edge_cnt].to = b;
    edges[edge_cnt].t = t;
    edges[edge_cnt].next = adj_head_arr[a];
    adj_head_arr[a] = edge_cnt++;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    int r[MAX_N];
    for(int i=1;i<=n;i++) scanf("%d", &r[i]);
    
    for(int i=0;i<m;i++){
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        addEdge(a, b, t);
        addEdge(b, a, t);
    }
    
    // Compute Dk for each k
    int Dk[MAX_K][MAX_N];
    for(int k=1;k<=10;k++){
        for(int i=1;i<=n;i++) Dk[k][i] = INF;
        // Initialize heap with Hk = servers with r(u) >k
        MinHeap heap;
        initHeap(&heap, n);
        for(int i=1;i<=n;i++) {
            if(r[i] > k){
                Dk[k][i] = 0;
                pushHeap(&heap, i, 0);
            }
        }
        // Multi-source Dijkstra
        while(heap.size >0){
            HeapNode current = popHeap(&heap);
            int u = current.v;
            int d = current.dist;
            if(d > Dk[k][u]) continue;
            for(int e = adj_head_arr[u]; e != -1; e = edges[e].next){
                int v = edges[e].to;
                int nd = d + edges[e].t;
                if(nd < Dk[k][v]){
                    Dk[k][v] = nd;
                    pushHeap(&heap, v, nd);
                }
            }
        }
        freeHeap(&heap);
    }
    
    // Prepare Wk lists
    int Wk_count[MAX_K] = {0};
    int *Wk[MAX_K];
    for(int k=1;k<=10;k++) Wk[k] = (int*)malloc(sizeof(int)*n);
    for(int i=1;i<=n;i++) {
        int k = r[i];
        Wk[k][Wk_count[k]++] = i;
    }
    
    // Initialize last_visit
    int *last_visit = (int*)calloc(n+1, sizeof(int));
    int current_w_id = 0;
    long long total_count =0;
    
    // Initialize a heap for counting
    MinHeap heap_count;
    initHeap(&heap_count, n);
    
    for(int k=1;k<=10;k++){
        for(int i=0;i<Wk_count[k];i++){
            int w = Wk[k][i];
            current_w_id++;
            // Initialize heap for this w
            heap_count.size =0;
            pushHeap(&heap_count, w, 0);
            while(heap_count.size >0){
                HeapNode current = popHeap(&heap_count);
                int u = current.v;
                int du = current.dist;
                if(du >= Dk[k][u]) continue;
                if(last_visit[u] == current_w_id) continue;
                last_visit[u] = current_w_id;
                total_count++;
                for(int e = adj_head_arr[u]; e != -1; e = edges[e].next){
                    int v = edges[e].to;
                    int nv = du + edges[e].t;
                    if(nv < Dk[k][v]){
                        pushHeap(&heap_count, v, nv);
                    }
                }
            }
        }
    }
    
    printf("%lld\n", total_count);
    
    // Free memory
    for(int k=1;k<=10;k++) free(Wk[k]);
    free(heap_count.data);
    free(last_visit);
    
    return 0;
}