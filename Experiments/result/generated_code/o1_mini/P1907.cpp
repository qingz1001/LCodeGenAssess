#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_NODES 1002
#define INF 1e18

typedef struct Edge {
    int to;
    double cost;
    struct Edge* next;
} Edge;

typedef struct {
    int node;
    double dist;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap* heap, int idx) {
    while (idx > 0) {
        int parent = (idx -1)/2;
        if (heap->data[parent].dist > heap->data[idx].dist) {
            swap(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
        else break;
    }
}

void heapifyDown(MinHeap* heap, int idx) {
    while (2*idx +1 < heap->size) {
        int smallest = idx;
        int left = 2*idx +1;
        int right = 2*idx +2;
        if (heap->data[left].dist < heap->data[smallest].dist)
            smallest = left;
        if (right < heap->size && heap->data[right].dist < heap->data[smallest].dist)
            smallest = right;
        if (smallest != idx) {
            swap(&heap->data[smallest], &heap->data[idx]);
            idx = smallest;
        }
        else break;
    }
}

void insertHeap(MinHeap* heap, int node, double dist) {
    if (heap->size == heap->capacity) return;
    heap->data[heap->size].node = node;
    heap->data[heap->size].dist = dist;
    heapifyUp(heap, heap->size);
    heap->size++;
}

HeapNode extractMin(MinHeap* heap) {
    HeapNode min = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    heapifyDown(heap, 0);
    return min;
}

int isEmpty(MinHeap* heap) {
    return heap->size == 0;
}

int main(){
    double dirt_cost, rome_cost;
    scanf("%lf %lf", &dirt_cost, &rome_cost);
    
    int N;
    scanf("%d", &N);
    
    double coords[MAX_NODES][2];
    for(int i=1;i<=N;i++) {
        scanf("%lf %lf", &coords[i][0], &coords[i][1]);
    }
    
    bool isRomeRoad[MAX_NODES][MAX_NODES];
    for(int i=0;i<=N+1;i++)
        for(int j=0;j<=N+1;j++)
            isRomeRoad[i][j] = false;
    
    int a, b;
    while(scanf("%d %d", &a, &b)==2){
        if(a ==0 && b ==0) break;
        isRomeRoad[a][b] = true;
        isRomeRoad[b][a] = true;
    }
    
    double pier[2], home_coords[2];
    scanf("%lf %lf", &pier[0], &pier[1]);
    scanf("%lf %lf", &home_coords[0], &home_coords[1]);
    coords[0][0] = pier[0];
    coords[0][1] = pier[1];
    coords[N+1][0] = home_coords[0];
    coords[N+1][1] = home_coords[1];
    
    Edge* adj[MAX_NODES];
    for(int i=0;i<=N+1;i++) adj[i] = NULL;
    
    for(int i=0;i<=N+1;i++){
        for(int j=i+1;j<=N+1;j++){
            double dx = coords[i][0] - coords[j][0];
            double dy = coords[i][1] - coords[j][1];
            double distance = sqrt(dx*dx + dy*dy);
            double cost;
            if(i>=1 && i<=N && j>=1 && j<=N && isRomeRoad[i][j]){
                cost = rome_cost * distance;
            }
            else{
                cost = dirt_cost * distance;
            }
            // Add edge i to j
            Edge* edge1 = (Edge*)malloc(sizeof(Edge));
            edge1->to = j;
            edge1->cost = cost;
            edge1->next = adj[i];
            adj[i] = edge1;
            // Add edge j to i
            Edge* edge2 = (Edge*)malloc(sizeof(Edge));
            edge2->to = i;
            edge2->cost = cost;
            edge2->next = adj[j];
            adj[j] = edge2;
        }
    }
    
    // Connect pier (0) to all intersections and home
    for(int i=1;i<=N+1;i++){
        double dx = coords[0][0] - coords[i][0];
        double dy = coords[0][1] - coords[i][1];
        double distance = sqrt(dx*dx + dy*dy);
        double cost = dirt_cost * distance;
        // Add edge 0 to i
        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = i;
        edge1->cost = cost;
        edge1->next = adj[0];
        adj[0] = edge1;
        // Add edge i to 0
        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = 0;
        edge2->cost = cost;
        edge2->next = adj[i];
        adj[i] = edge2;
    }
    
    // Connect home (N+1) to all intersections and pier
    for(int i=0;i<=N;i++){
        double dx = coords[N+1][0] - coords[i][0];
        double dy = coords[N+1][1] - coords[i][1];
        double distance = sqrt(dx*dx + dy*dy);
        double cost = dirt_cost * distance;
        // Add edge N+1 to i
        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = i;
        edge1->cost = cost;
        edge1->next = adj[N+1];
        adj[N+1] = edge1;
        // Add edge i to N+1
        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = N+1;
        edge2->cost = cost;
        edge2->next = adj[i];
        adj[i] = edge2;
    }
    
    double dist_arr[MAX_NODES];
    for(int i=0;i<=N+1;i++) dist_arr[i] = INF;
    dist_arr[0] = 0.0;
    
    bool visited[MAX_NODES];
    for(int i=0;i<=N+1;i++) visited[i] = false;
    
    MinHeap* heap = createHeap(MAX_NODES*2);
    insertHeap(heap, 0, 0.0);
    
    while(!isEmpty(heap)){
        HeapNode current = extractMin(heap);
        int u = current.node;
        if(visited[u]) continue;
        visited[u] = true;
        Edge* e = adj[u];
        while(e){
            int v = e->to;
            double new_dist = dist_arr[u] + e->cost;
            if(new_dist < dist_arr[v]){
                dist_arr[v] = new_dist;
                insertHeap(heap, v, dist_arr[v]);
            }
            e = e->next;
        }
    }
    
    printf("%.4lf\n", dist_arr[N+1]);
    
    // Free memory
    for(int i=0;i<=N+1;i++){
        Edge* e = adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(heap->data);
    free(heap);
    
    return 0;
}