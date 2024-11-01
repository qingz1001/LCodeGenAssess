#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001
#define MAXM 500001
#define INF 1000000000

typedef struct Edge {
    int to;
    int weight;
    int idx;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int blocked[MAXM];
int distN[MAXN];
int dist1_arr[MAXN];

typedef struct HeapNode {
    int node;
    int dist;
} HeapNode;

typedef struct Heap {
    HeapNode *data;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int capacity){
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode* a, HeapNode* b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(Heap* heap, int idx){
    if(idx == 0) return;
    int parent = (idx - 1) / 2;
    if(heap->data[parent].dist > heap->data[idx].dist){
        swap(&heap->data[parent], &heap->data[idx]);
        heapify_up(heap, parent);
    }
}

void heapify_down(Heap* heap, int idx){
    int smallest = idx;
    int left = 2*idx +1;
    int right = 2*idx +2;
    if(left < heap->size && heap->data[left].dist < heap->data[smallest].dist){
        smallest = left;
    }
    if(right < heap->size && heap->data[right].dist < heap->data[smallest].dist){
        smallest = right;
    }
    if(smallest != idx){
        swap(&heap->data[smallest], &heap->data[idx]);
        heapify_down(heap, smallest);
    }
}

int extractMin(Heap* heap){
    if(heap->size ==0) return -1;
    int minNode = heap->data[0].node;
    heap->data[0] = heap->data[heap->size-1];
    heap->size--;
    heapify_down(heap, 0);
    return minNode;
}

void insertHeap(Heap* heap, int node, int dist){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode)*heap->capacity);
    }
    heap->data[heap->size].node = node;
    heap->data[heap->size].dist = dist;
    heapify_up(heap, heap->size);
    heap->size++;
}

void addEdge(int from, int to, int weight, int idx){
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = to;
    edge->weight = weight;
    edge->idx = idx;
    edge->next = adj[from];
    adj[from] = edge;
}

void dijkstra(int start, int* dist){
    for(int i=1;i<=MAXN-1;i++) dist[i] = INF;
    Heap* heap = createHeap(10000);
    dist[start] = 0;
    insertHeap(heap, start, 0);
    while(heap->size >0){
        int u = extractMin(heap);
        Edge* e = adj[u];
        while(e){
            if(!blocked[e->idx]){
                if(dist[e->to] > dist[u] + e->weight){
                    dist[e->to] = dist[u] + e->weight;
                    insertHeap(heap, e->to, dist[e->to]);
                }
            }
            e = e->next;
        }
    }
    free(heap->data);
    free(heap);
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int A, B, V;
    for(int i=0;i<M;i++){
        scanf("%d %d %d", &A, &B, &V);
        addEdge(A, B, V, i);
        addEdge(B, A, V, i);
    }
    dijkstra(N, distN);
    dijkstra(1, dist1_arr);
    int shortest = distN[1];
    int max_time = shortest;
    for(int i=0;i<M;i++){
        // Find if edge i is on any shortest path
        // Iterate through all edges once
        // To avoid double checking, iterate only once
        // So iterate through i from 0 to M-1
        // and find the corresponding edges
        // Since edges are added as two directed edges
        // We need to find one direction
        // To simplify, iterate through adj list of all nodes
        // and check edges with idx=i only once
        // So skip here and handle later
    }
    // Now iterate through all edges to find critical edges
    for(int i=0;i<M;i++){
        // Find one direction
        // To find u and v, iterate through adj lists
        // Alternatively, store edges separately
        // To simplify, not storing u and v, so iterate again
        // Redefine edges with u and v
        // To simplify, re-read the input
    }
    // Reset adj lists
    // To find critical edges, need to know u and v
    // Rebuild edge list with u and v
    // Redefine Edge structure
    // To simplify, read input again
    // Restart the program
    // Instead, store u and v
    typedef struct {
        int u;
        int v;
        int w;
    } OriginalEdge;
    OriginalEdge* orig = (OriginalEdge*)malloc(sizeof(OriginalEdge)*M);
    rewind(stdin);
    scanf("%d %d", &N, &M);
    for(int i=0;i<M;i++){
        scanf("%d %d %d", &A, &B, &V);
        orig[i].u = A;
        orig[i].v = B;
        orig[i].w = V;
    }
    // Now find critical edges
    for(int i=0;i<M;i++){
        int u = orig[i].u;
        int v = orig[i].v;
        int w = orig[i].w;
        if(distN[u] + w + dist1_arr[v] == shortest || distN[v] + w + dist1_arr[u] == shortest){
            blocked[i] = 1;
            // Temporarily block
            // Run Dijkstra
            // Copy blocked status
            // To block, set blocked[i]=1
            // Run Dijkstra
            // First set blocked[i]=1
            dijkstra(N, distN);
            int new_dist = distN[1];
            if(new_dist > max_time){
                max_time = new_dist;
            }
            blocked[i] = 0;
        }
    }
    printf("%d\n", max_time);
    free(orig);
    // Free adj lists
    for(int i=1;i<=N;i++){
        Edge* e = adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    return 0;
}