#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXN 1002
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

Edge* adj[MAXN];
int N;
double x_coords[MAXN], y_coords[MAXN];
int roads_matrix[1000][1000];
double dirt, rome;

// Min-heap implementation
typedef struct {
    HeapNode* data;
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

void pushHeap(MinHeap* heap, int node, double dist){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode)*heap->capacity);
    }
    heap->data[heap->size].node = node;
    heap->data[heap->size].dist = dist;
    int i = heap->size++;
    while(i !=0){
        int parent = (i-1)/2;
        if(heap->data[parent].dist > heap->data[i].dist){
            swap(&heap->data[parent], &heap->data[i]);
            i = parent;
        }
        else break;
    }
}

HeapNode popHeap(MinHeap* heap){
    HeapNode top = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    int i=0;
    while(1){
        int smallest = i;
        int l = 2*i+1;
        int r = 2*i+2;
        if(l < heap->size && heap->data[l].dist < heap->data[smallest].dist){
            smallest = l;
        }
        if(r < heap->size && heap->data[r].dist < heap->data[smallest].dist){
            smallest = r;
        }
        if(smallest != i){
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int isEmpty(MinHeap* heap){
    return heap->size ==0;
}

int main(){
    // Initialize roads_matrix to 0
    memset(roads_matrix, 0, sizeof(roads_matrix));
    // Read dirt and rome dissatisfaction
    scanf("%lf %lf", &dirt, &rome);
    // Read N
    scanf("%d", &N);
    // Read N intersections
    for(int i=0;i<N;i++) scanf("%lf %lf", &x_coords[i], &y_coords[i]);
    // Read roads list
    int i, j;
    while(scanf("%d %d", &i, &j)){
        if(i ==0 && j==0) break;
        roads_matrix[i-1][j-1] = roads_matrix[j-1][i-1] =1;
    }
    // Read dock and home coordinates
    double dock_x, dock_y, home_x, home_y;
    scanf("%lf %lf", &dock_x, &dock_y);
    scanf("%lf %lf", &home_x, &home_y);
    // Add dock and home as nodes N and N+1
    x_coords[N] = dock_x;
    y_coords[N] = dock_y;
    x_coords[N+1] = home_x;
    y_coords[N+1] = home_y;
    // Build adjacency list
    for(int u=0; u<N+2; u++){
        adj[u] = NULL;
    }
    // Roads between intersections
    for(int u=0; u<N; u++){
        for(int v=u+1; v<N; v++){
            double dx = x_coords[u] - x_coords[v];
            double dy = y_coords[u] - y_coords[v];
            double distance = sqrt(dx*dx + dy*dy);
            double cost;
            if(roads_matrix[u][v]){
                cost = distance * rome;
            }
            else{
                cost = distance * dirt;
            }
            Edge* edge1 = (Edge*)malloc(sizeof(Edge));
            edge1->to = v;
            edge1->cost = cost;
            edge1->next = adj[u];
            adj[u] = edge1;
            Edge* edge2 = (Edge*)malloc(sizeof(Edge));
            edge2->to = u;
            edge2->cost = cost;
            edge2->next = adj[v];
            adj[v] = edge2;
        }
    }
    // Roads from dock (N) to all intersections
    for(int u=0; u<N; u++){
        double dx = x_coords[u] - x_coords[N];
        double dy = y_coords[u] - y_coords[N];
        double distance = sqrt(dx*dx + dy*dy);
        double cost = distance * dirt;
        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = u;
        edge1->cost = cost;
        edge1->next = adj[N];
        adj[N] = edge1;
        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = N;
        edge2->cost = cost;
        edge2->next = adj[u];
        adj[u] = edge2;
    }
    // Roads from all intersections to home (N+1)
    for(int u=0; u<N; u++){
        double dx = x_coords[u] - x_coords[N+1];
        double dy = y_coords[u] - y_coords[N+1];
        double distance = sqrt(dx*dx + dy*dy);
        double cost = distance * dirt;
        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = N+1;
        edge1->cost = cost;
        edge1->next = adj[u];
        adj[u] = edge1;
        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = u;
        edge2->cost = cost;
        edge2->next = adj[N+1];
        adj[N+1] = edge2;
    }
    // Initialize distance array
    double dist[MAXN];
    for(int u=0; u<N+2; u++) dist[u] = INF;
    dist[N] =0.0;
    // Initialize heap
    MinHeap* heap = createHeap(2*(N+2));
    pushHeap(heap, N, 0.0);
    // Dijkstra
    int visited_flag[MAXN];
    memset(visited_flag, 0, sizeof(visited_flag));
    while(!isEmpty(heap)){
        HeapNode current = popHeap(heap);
        int u = current.node;
        if(visited_flag[u]) continue;
        visited_flag[u] =1;
        if(u == N+1) break;
        for(Edge* edge = adj[u]; edge != NULL; edge = edge->next){
            int v = edge->to;
            double new_dist = dist[u] + edge->cost;
            if(new_dist < dist[v]){
                dist[v] = new_dist;
                pushHeap(heap, v, dist[v]);
            }
        }
    }
    printf("%.4lf\n", dist[N+1]);
    // Free memory
    for(int u=0; u<N+2; u++){
        Edge* edge = adj[u];
        while(edge){
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(heap->data);
    free(heap);
    return 0;
}