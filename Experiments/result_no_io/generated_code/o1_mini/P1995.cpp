#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAXN 4002
#define MAXM (MAXN * MAXN)
#define INF 1e18

typedef struct {
    double x, y;
} Point;

typedef struct Edge {
    int to;
    double weight;
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

// Global variables
int n;
Point points[MAXN];
int m = 0;
AdjList adj[MAXN];
double x_S, y_S, x_T, y_T, v;

// Function to compare two points for uniqueness
int cmp_point(const void* a, const void* b) {
    Point* pa = (Point*)a;
    Point* pb = (Point*)b;
    if (pa->x < pb->x) return -1;
    if (pa->x > pb->x) return 1;
    if (pa->y < pb->y) return -1;
    if (pa->y > pb->y) return 1;
    return 0;
}

// Function to check if a point is inside any rectangle
bool point_in_rect(double x, double y) {
    for(int i=0;i<n;i++) {
        if(x >= (double)(points[4*i].x) && x <= (double)(points[4*i+2].x) &&
           y >= (double)(points[4*i].y) && y <= (double)(points[4*i+1].y)) {
            return true;
        }
    }
    return false;
}

// Function to check if a line segment is entirely within the union of rectangles
bool is_visible(Point a, Point b) {
    // Sampling approach
    int SAMPLE = 100;
    for(int i=0;i<=SAMPLE;i++) {
        double t = (double)i / SAMPLE;
        double x = a.x + (b.x - a.x) * t;
        double y = a.y + (b.y - a.y) * t;
        bool inside = false;
        for(int j=0;j<n;j++) {
            double x1 = points[4*j].x;
            double y1 = points[4*j].y;
            double x2 = points[4*j+2].x;
            double y2 = points[4*j+1].y;
            if(x >= x1 - 1e-9 && x <= x2 + 1e-9 && y >= y1 - 1e-9 && y <= y2 + 1e-9){
                inside = true;
                break;
            }
        }
        if(!inside) return false;
    }
    return true;
}

// Min Heap functions
MinHeap* create_heap(int capacity){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap_heapnode(HeapNode* a, HeapNode* b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heap_push(MinHeap* heap, HeapNode node){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode)*heap->capacity);
    }
    heap->data[heap->size] = node;
    int i = heap->size;
    heap->size++;
    while(i > 0){
        int parent = (i - 1) / 2;
        if(heap->data[parent].dist <= heap->data[i].dist) break;
        swap_heapnode(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

HeapNode heap_pop(MinHeap* heap){
    HeapNode top = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int i = 0;
    while(1){
        int left = 2*i +1;
        int right = 2*i +2;
        int smallest = i;
        if(left < heap->size && heap->data[left].dist < heap->data[smallest].dist){
            smallest = left;
        }
        if(right < heap->size && heap->data[right].dist < heap->data[smallest].dist){
            smallest = right;
        }
        if(smallest != i){
            swap_heapnode(&heap->data[smallest], &heap->data[i]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int main(){
    scanf("%d", &n);
    // Read rectangles and store their corners
    for(int i=0;i<n;i++){
        double x1, y1, x2, y2;
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        points[m].x = x1; points[m].y = y1; m++;
        points[m].x = x1; points[m].y = y2; m++;
        points[m].x = x2; points[m].y = y1; m++;
        points[m].x = x2; points[m].y = y2; m++;
    }
    // Read S
    scanf("%lf %lf", &x_S, &y_S);
    points[m].x = x_S; points[m].y = y_S; m++;
    // Read T
    scanf("%lf %lf", &x_T, &y_T);
    points[m].x = x_T; points[m].y = y_T; m++;
    // Read v
    scanf("%lf", &v);
    // Sort and remove duplicates
    qsort(points, m, sizeof(Point), cmp_point);
    int unique = 1;
    for(int i=1;i<m;i++){
        if(!(fabs(points[i].x - points[i-1].x) < 1e-9 && fabs(points[i].y - points[i-1].y) < 1e-9)){
            points[unique++] = points[i];
        }
    }
    m = unique;
    // Build visibility graph
    for(int i=0;i<m;i++){
        for(int j=i+1;j<m;j++){
            if(is_visible(points[i], points[j])){
                double dx = points[i].x - points[j].x;
                double dy = points[i].y - points[j].y;
                double dist = sqrt(dx*dx + dy*dy) / v;
                Edge* e1 = (Edge*)malloc(sizeof(Edge));
                e1->to = j;
                e1->weight = dist;
                e1->next = adj[i].head;
                adj[i].head = e1;
                Edge* e2 = (Edge*)malloc(sizeof(Edge));
                e2->to = i;
                e2->weight = dist;
                e2->next = adj[j].head;
                adj[j].head = e2;
            }
        }
    }
    // Find indices of S and T
    int S = -1, T_idx = -1;
    for(int i=0;i<m;i++){
        if(fabs(points[i].x - x_S) < 1e-9 && fabs(points[i].y - y_S) < 1e-9){
            S = i;
        }
        if(fabs(points[i].x - x_T) < 1e-9 && fabs(points[i].y - y_T) < 1e-9){
            T_idx = i;
        }
    }
    // Dijkstra
    double dist_arr[m];
    for(int i=0;i<m;i++) dist_arr[i] = INF;
    dist_arr[S] = 0.0;
    MinHeap* heap = create_heap( m < 1024 ? 1024 : m );
    HeapNode start;
    start.id = S;
    start.dist = 0.0;
    heap_push(heap, start);
    bool visited[m];
    for(int i=0;i<m;i++) visited[i] = false;
    while(heap->size >0){
        HeapNode current = heap_pop(heap);
        if(visited[current.id]) continue;
        visited[current.id] = true;
        if(current.id == T_idx) break;
        for(Edge* e = adj[current.id].head; e != NULL; e = e->next){
            if(!visited[e->to] && dist_arr[e->to] > dist_arr[current.id] + e->weight){
                dist_arr[e->to] = dist_arr[current.id] + e->weight;
                HeapNode neighbor;
                neighbor.id = e->to;
                neighbor.dist = dist_arr[e->to];
                heap_push(heap, neighbor);
            }
        }
    }
    printf("%.10lf\n", dist_arr[T_idx]);
    return 0;
}