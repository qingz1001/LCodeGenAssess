#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50005
#define INF 100000000000000LL

typedef long long ll;

typedef struct Edge {
    int to;
    ll weight;
    struct Edge* next;
} Edge;

Edge* graph[MAXN];
ll dist_val[MAXN];
int prev_node[MAXN];
int n, m;
ll v[MAXN];

typedef struct HeapNode {
    int u;
    ll dist;
} HeapNode;

typedef struct MinHeap {
    int size;
    int capacity;
    HeapNode* array;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    return heap;
}

void swapHeapNode(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2*idx +1;
    int right = 2*idx +2;
    if(left < heap->size && heap->array[left].dist < heap->array[smallest].dist)
        smallest = left;
    if(right < heap->size && heap->array[right].dist < heap->array[smallest].dist)
        smallest = right;
    if(smallest != idx){
        swapHeapNode(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

int isEmpty(MinHeap* heap){
    return heap->size ==0;
}

HeapNode extractMin(MinHeap* heap){
    HeapNode root = heap->array[0];
    heap->array[0] = heap->array[heap->size -1];
    heap->size--;
    minHeapify(heap, 0);
    return root;
}

void decreaseKey(MinHeap* heap, int u, ll dist){
    for(int i=0;i<heap->size;i++) {
        if(heap->array[i].u == u){
            heap->array[i].dist = dist;
            while(i !=0 && heap->array[(i-1)/2].dist > heap->array[i].dist){
                swapHeapNode(&heap->array[i], &heap->array[(i-1)/2]);
                i = (i-1)/2;
            }
            break;
        }
    }
}

int inHeap[MAXN];

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%lld", &v[i]);
    // Initialize graph
    for(int i=1;i<=n;i++) graph[i] = NULL;
    // Read group tunnels
    for(int i=0;i<m;i++){
        int s_l, s_r, t_l, t_r;
        ll w;
        scanf("%d %d %d %d %lld", &s_l, &s_r, &t_l, &t_r, &w);
        for(int u = s_l; u <= s_r; u++){
            for(int v_t = t_l; v_t <= t_r; v_t++){
                Edge* newEdge = (Edge*)malloc(sizeof(Edge));
                newEdge->to = v_t;
                newEdge->weight = w;
                newEdge->next = graph[u];
                graph[u] = newEdge;
            }
        }
    }
    // Add digging tunnels
    for(int u=1; u<=n; u++){
        if(v[u] !=0){
            for(int j=1; j<=n; j++){
                if(u == j) continue;
                ll cost = (ll)(abs(u - j)) * v[u];
                Edge* newEdge = (Edge*)malloc(sizeof(Edge));
                newEdge->to = j;
                newEdge->weight = cost;
                newEdge->next = graph[u];
                graph[u] = newEdge;
            }
        }
    }
    // Dijkstra
    for(int i=1;i<=n;i++) dist_val[i] = INF, prev_node[i] = -1;
    dist_val[1] = 0;
    MinHeap* heap = createMinHeap(n);
    heap->array[heap->size].u = 1;
    heap->array[heap->size].dist = 0;
    heap->size++;
    inHeap[1] = 1;
    while(!isEmpty(heap)){
        HeapNode min = extractMin(heap);
        int u = min.u;
        inHeap[u] = 0;
        for(Edge* edge = graph[u]; edge != NULL; edge = edge->next){
            int v_to = edge->to;
            if(dist_val[v_to] > dist_val[u] + edge->weight){
                dist_val[v_to] = dist_val[u] + edge->weight;
                prev_node[v_to] = u;
                if(!inHeap[v_to]){
                    heap->array[heap->size].u = v_to;
                    heap->array[heap->size].dist = dist_val[v_to];
                    heap->size++;
                    inHeap[v_to] =1;
                    int i = heap->size -1;
                    while(i !=0 && heap->array[(i-1)/2].dist > heap->array[i].dist){
                        swapHeapNode(&heap->array[i], &heap->array[(i-1)/2]);
                        i = (i-1)/2;
                    }
                }
            }
        }
    }
    if(dist_val[n] == INF){
        printf("-1\n");
        return 0;
    }
    printf("%lld\n", dist_val[n]);
    // Reconstruct path
    int path[MAXN];
    int cnt =0;
    int current = n;
    while(current != -1){
        path[cnt++] = current;
        current = prev_node[current];
    }
    if(path[cnt-1] !=1){
        printf("0\n");
        return 0;
    }
    printf("%d\n", cnt);
    for(int i=cnt-1;i>=0;i--){
        printf("%d ", path[i]);
    }
    printf("\n");
    return 0;
}