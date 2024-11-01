#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_S 100
#define MAX_NODES (4 * MAX_S)
#define MAX_EDGES (4 * MAX_S + 16 * MAX_S * (MAX_S -1)/2)
#define INF 1e18

typedef struct Edge {
    int to;
    double cost;
    struct Edge* next;
} Edge;

typedef struct {
    Edge* head;
} AdjList;

typedef struct {
    double dist;
    int id;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

// Function to add edge to adjacency list
void add_edge(AdjList adj[], int from, int to, double cost){
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = to;
    edge->cost = cost;
    edge->next = adj[from].head;
    adj[from].head = edge;
}

// Heap functions
MinHeap* create_heap(int capacity){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode)*capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap_heapnode(HeapNode* a, HeapNode* b){
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify_up(MinHeap* heap, int idx){
    while(idx > 0){
        int parent = (idx -1)/2;
        if(heap->data[parent].dist > heap->data[idx].dist){
            swap_heapnode(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
        else break;
    }
}

void heapify_down(MinHeap* heap, int idx){
    while(2*idx+1 < heap->size){
        int smallest = idx;
        int left = 2*idx+1;
        int right = 2*idx+2;
        if(left < heap->size && heap->data[left].dist < heap->data[smallest].dist){
            smallest = left;
        }
        if(right < heap->size && heap->data[right].dist < heap->data[smallest].dist){
            smallest = right;
        }
        if(smallest != idx){
            swap_heapnode(&heap->data[smallest], &heap->data[idx]);
            idx = smallest;
        }
        else break;
    }
}

int is_empty(MinHeap* heap){
    return heap->size == 0;
}

HeapNode pop_heap(MinHeap* heap){
    HeapNode top = heap->data[0];
    heap->data[0] = heap->data[heap->size-1];
    heap->size--;
    heapify_down(heap, 0);
    return top;
}

void push_heap(MinHeap* heap, HeapNode node){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode)*heap->capacity);
    }
    heap->data[heap->size] = node;
    heapify_up(heap, heap->size);
    heap->size++;
}

// Dijkstra's algorithm
double dijkstra(AdjList adj[], int total_nodes, int* start, int start_size, int* end, int end_size){
    double dist[MAX_NODES];
    for(int i=0;i<total_nodes;i++) dist[i] = INF;
    MinHeap* heap = create_heap(total_nodes);
    for(int i=0;i<start_size;i++){
        dist[start[i]] = 0.0;
        HeapNode node;
        node.dist = 0.0;
        node.id = start[i];
        push_heap(heap, node);
    }
    while(!is_empty(heap)){
        HeapNode current = pop_heap(heap);
        if(current.dist > dist[current.id]) continue;
        // Check if current.id is one of the end nodes
        for(int i=0;i<end_size;i++) if(current.id == end[i]) { free(heap->data); free(heap); return current.dist;}
        Edge* edge = adj[current.id].head;
        while(edge){
            if(dist[edge->to] > dist[current.id] + edge->cost){
                dist[edge->to] = dist[current.id] + edge->cost;
                HeapNode node;
                node.dist = dist[edge->to];
                node.id = edge->to;
                push_heap(heap, node);
            }
            edge = edge->next;
        }
    }
    free(heap->data);
    free(heap);
    // Find minimum distance among end nodes
    double res = INF;
    for(int i=0;i<end_size;i++) if(dist[end[i]] < res) res = dist[end[i]];
    return res;
}

int main(){
    int n;
    scanf("%d", &n);
    while(n--){
        int S;
        double t;
        int A, B;
        scanf("%d %lf %d %d", &S, &t, &A, &B);
        // Store airports
        double cities_x[MAX_S][4];
        double cities_y[MAX_S][4];
        double T[MAX_S];
        for(int i=0;i<S;i++){
            double x1,y1,x2,y2,x3,y3,Ti;
            scanf("%lf %lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3, &Ti);
            // Find D
            double D_x, D_y;
            // Midpoints
            // Option1: A and D1 are diagonal
            double mid1_x = (x1 + x2)/2.0, mid1_y = (y1 + y2)/2.0;
            double mid2_x = (x1 + x3)/2.0, mid2_y = (y1 + y3)/2.0;
            double mid3_x = (x2 + x3)/2.0, mid3_y = (y2 + y3)/2.0;
            // Midpoint of A and D1 should equal midpoint of B and C
            // Check D1 = B + C - A = x2 + x3 - x1, y2 + y3 - y1
            double Dx1 = x2 + x3 - x1;
            double Dy1 = y2 + y3 - y1;
            double mx1 = (x1 + Dx1)/2.0, my1 = (y1 + Dy1)/2.0;
            if(fabs(mx1 - (x2 + x3)/2.0) < 1e-6 && fabs(my1 - (y2 + y3)/2.0) <1e-6){
                D_x = Dx1;
                D_y = Dy1;
            }
            else{
                // Check D2 = A + C - B
                double Dx2 = x1 + x3 - x2;
                double Dy2 = y1 + y3 - y2;
                double mx2 = (x2 + Dx2)/2.0, my2 = (y2 + Dy2)/2.0;
                if(fabs(mx2 - (x1 + x3)/2.0) <1e-6 && fabs(my2 - (y1 + y3)/2.0) <1e-6){
                    D_x = Dx2;
                    D_y = Dy2;
                }
                else{
                    // D3 = A + B - C
                    double Dx3 = x1 + x2 - x3;
                    double Dy3 = y1 + y2 - y3;
                    D_x = Dx3;
                    D_y = Dy3;
                }
            }
            cities_x[i][0] = x1;
            cities_y[i][0] = y1;
            cities_x[i][1] = x2;
            cities_y[i][1] = y2;
            cities_x[i][2] = x3;
            cities_y[i][2] = y3;
            cities_x[i][3] = D_x;
            cities_y[i][3] = D_y;
            T[i] = Ti;
        }
        // Assign node IDs
        // 0 to 4*S-1
        int total_nodes = 4*S;
        AdjList adj[MAX_NODES];
        for(int i=0;i<total_nodes;i++) adj[i].head = NULL;
        // Add rail edges within cities
        for(int i=0;i<S;i++){
            double Ti = T[i];
            for(int j=0;j<4;j++){
                for(int k=j+1;k<4;k++){
                    // Check if j and k are connected in rectangle
                    // In rectangle, each vertex connected to two others
                    // For simplicity, connect j to k if they form an edge
                    // Since it's rectangle, opposite vertices are not directly connected
                    // So connect each vertex to next vertex and to one other
                    // To determine, let's connect in order
                }
            }
            // To connect rectangle edges, assume the four points are in order
            // Connect 0-1,1-2,2-3,3-0
            int base = i*4;
            // Calculate which points are adjacent
            // To ensure it's rectangle, maybe...
            // Alternatively, connect all pairs and rely on Dijkstra
            // But better to connect edges properly
            // Connect 0-1,1-3,3-2,2-0
            // To make it general, connect all four edges of rectangle
            // Assuming the points are in some order, but since we computed D, connect all four edges
            // Connect 0-1,1-2,2-3,3-0
            double x0 = cities_x[i][0], y0 = cities_y[i][0];
            double x1 = cities_x[i][1], y1 = cities_y[i][1];
            double x2 = cities_x[i][2], y2 = cities_y[i][2];
            double x3 = cities_x[i][3], y3 = cities_y[i][3];
            // To find the rectangle edges, connect each point to two others that form right angles
            // Compute distances and connect accordingly
            // To simplify, connect in the order the points were added
            // Connect 0-1, 1-3, 3-2, 2-0
            // This should form the rectangle
            add_edge(adj, base+0, base+1, Ti * sqrt((x0 - x1)*(x0 - x1)+(y0 - y1)*(y0 - y1)));
            add_edge(adj, base+1, base+0, Ti * sqrt((x0 - x1)*(x0 - x1)+(y0 - y1)*(y0 - y1)));
            add_edge(adj, base+1, base+3, Ti * sqrt((x1 - x3)*(x1 - x3)+(y1 - y3)*(y1 - y3)));
            add_edge(adj, base+3, base+1, Ti * sqrt((x1 - x3)*(x1 - x3)+(y1 - y3)*(y1 - y3)));
            add_edge(adj, base+3, base+2, Ti * sqrt((x3 - x2)*(x3 - x2)+(y3 - y2)*(y3 - y2)));
            add_edge(adj, base+2, base+3, Ti * sqrt((x3 - x2)*(x3 - x2)+(y3 - y2)*(y3 - y2)));
            add_edge(adj, base+2, base+0, Ti * sqrt((x2 - x0)*(x2 - x0)+(y2 - y0)*(y2 - y0)));
            add_edge(adj, base+0, base+2, Ti * sqrt((x2 - x0)*(x2 - x0)+(y2 - y0)*(y2 - y0)));
        }
        // Add flight edges between different cities
        for(int i=0;i<S;i++) {
            for(int j=i+1;j<S;j++) {
                for(int a=0;a<4;a++) {
                    for(int b=0;b<4;b++) {
                        double dx = cities_x[i][a] - cities_x[j][b];
                        double dy = cities_y[i][a] - cities_y[j][b];
                        double dist = sqrt(dx*dx + dy*dy);
                        double cost = t * dist;
                        int from = i*4 + a;
                        int to = j*4 + b;
                        add_edge(adj, from, to, cost);
                        add_edge(adj, to, from, cost);
                    }
                }
            }
        }
        // Define start and end nodes
        int start_nodes[4];
        for(int i=0;i<4;i++) start_nodes[i] = (A-1)*4 + i;
        int end_nodes[4];
        for(int i=0;i<4;i++) end_nodes[i] = (B-1)*4 + i;
        // Run Dijkstra
        double result = dijkstra(adj, total_nodes, start_nodes, 4, end_nodes,4);
        printf("%.1lf\n", result);
        // Free adjacency list
        for(int i=0;i<total_nodes;i++) {
            Edge* edge = adj[i].head;
            while(edge){
                Edge* tmp = edge;
                edge = edge->next;
                free(tmp);
            }
        }
    }
}