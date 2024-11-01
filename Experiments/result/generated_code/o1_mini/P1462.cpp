#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 10005
#define MAXM 100005
#define INF 1000000000000000000LL

typedef long long ll;

typedef struct Edge {
    int to;
    ll cost;
    struct Edge* next;
} Edge;

typedef struct {
    Edge* head;
} AdjList;

AdjList adj[MAXN];

typedef struct {
    int node;
    ll dist;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

// Heap functions
MinHeap* createHeap(int capacity){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * (capacity + 1));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode* a, HeapNode* b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap* heap, int idx){
    while(idx > 1){
        int parent = idx / 2;
        if(heap->data[parent].dist > heap->data[idx].dist){
            swap(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
        else break;
    }
}

void heapify_down(MinHeap* heap, int idx){
    while(2*idx <= heap->size){
        int smallest = idx;
        int left = 2*idx;
        int right = 2*idx +1;
        if(left <= heap->size && heap->data[left].dist < heap->data[smallest].dist){
            smallest = left;
        }
        if(right <= heap->size && heap->data[right].dist < heap->data[smallest].dist){
            smallest = right;
        }
        if(smallest != idx){
            swap(&heap->data[smallest], &heap->data[idx]);
            idx = smallest;
        }
        else break;
    }
}

void pushHeap(MinHeap* heap, int node, ll dist){
    if(heap->size +1 > heap->capacity){
        // realloc if needed
        heap->capacity *=2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode)*(heap->capacity +1));
    }
    heap->size +=1;
    heap->data[heap->size].node = node;
    heap->data[heap->size].dist = dist;
    heapify_up(heap, heap->size);
}

HeapNode popHeap(MinHeap* heap){
    HeapNode top = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size -=1;
    heapify_down(heap, 1);
    return top;
}

ll dijkstra(int n, int f[], ll b, int max_fee){
    ll dist_arr[MAXN];
    for(int i=1;i<=n;i++) dist_arr[i]=INF;
    if(f[1] > max_fee) return INF;
    dist_arr[1] = 0;
    MinHeap* heap = createHeap(n);
    pushHeap(heap, 1, 0);
    while(heap->size >0){
        HeapNode current = popHeap(heap);
        int u = current.node;
        ll d = current.dist;
        if(u == n){
            free(heap->data);
            free(heap);
            return d;
        }
        if(d > dist_arr[u]) continue;
        Edge* e = adj[u].head;
        while(e){
            int v = e->to;
            ll nd = d + e->cost;
            if(f[v] <= max_fee && nd < dist_arr[v]){
                dist_arr[v] = nd;
                pushHeap(heap, v, nd);
            }
            e = e->next;
        }
    }
    free(heap->data);
    free(heap);
    return dist_arr[n];
}

int cmp_int(const void* a, const void* b){
    int aa = *(int*)a;
    int bb = *(int*)b;
    if(aa < bb) return -1;
    if(aa > bb) return 1;
    return 0;
}

int main(){
    int n, m;
    ll b;
    scanf("%d %d %lld", &n, &m, &b);
    int f[MAXN];
    for(int i=1;i<=n;i++) scanf("%d", &f[i]);
    // Initialize adjacency list
    for(int i=1;i<=n;i++) adj[i].head = NULL;
    // Read edges
    for(int i=0;i<m;i++){
        int a, c;
        ll cost;
        scanf("%d %d %lld", &a, &c, &cost);
        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = c;
        edge1->cost = cost;
        edge1->next = adj[a].head;
        adj[a].head = edge1;
        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = a;
        edge2->cost = cost;
        edge2->next = adj[c].head;
        adj[c].head = edge2;
    }
    // Collect unique f
    int unique_f[MAXN];
    int uf_size = 0;
    for(int i=1;i<=n;i++) unique_f[uf_size++] = f[i];
    qsort(unique_f, uf_size, sizeof(int), cmp_int);
    // Remove duplicates
    int unique_sorted[MAXN];
    int us_size =0;
    unique_sorted[us_size++] = unique_f[0];
    for(int i=1;i<uf_size;i++) {
        if(unique_f[i] != unique_f[i-1]){
            unique_sorted[us_size++] = unique_f[i];
        }
    }
    // Binary search
    int left = 0;
    int right = us_size -1;
    int answer = -1;
    while(left <= right){
        int mid = left + (right - left)/2;
        ll min_dmg = dijkstra(n, f, b, unique_sorted[mid]);
        if(min_dmg <= b){
            answer = unique_sorted[mid];
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    if(answer == -1){
        printf("AFK\n");
    }
    else{
        printf("%d\n", answer);
    }
    // Free memory
    for(int i=1;i<=n;i++){
        Edge* e = adj[i].head;
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    return 0;
}