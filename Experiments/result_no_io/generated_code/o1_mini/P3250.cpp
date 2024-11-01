#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005
#define LOG 17

typedef struct {
    int u, v, type, a, b, val, t, x;
} Event;

typedef struct {
    int parent[LOG];
    int depth;
    int in;
    int out;
} Node;

int n, m;
Node nodes[MAXN];
Event events[MAXM];
int timer_dfs = 0;

// LCA variables
int up[MAXN][LOG];
int depth_nodes[MAXN];

// Adjacency list
int adj[MAXN][20];
int adj_size[MAXN];

// Function to add edge
void add_edge(int u, int v){
    adj[u][adj_size[u]++] = v;
    adj[v][adj_size[v]++] = u;
}

// DFS to compute in, out and up tables
void dfs(int v, int parent_v){
    up[v][0] = parent_v;
    for(int i=1;i<LOG;i++) {
        up[v][i] = up[ up[v][i-1] ][i-1];
    }
    // Placeholder for in and out times if needed
    for(int i=0;i<adj_size[v];i++){
        int to = adj[v][i];
        if(to != parent_v){
            depth_nodes[to] = depth_nodes[v] + 1;
            dfs(to, v);
        }
    }
}

// Function to compute LCA
int lca_func(int a, int b){
    if(depth_nodes[a] < depth_nodes[b]){
        int temp = a;
        a = b;
        b = temp;
    }
    for(int k=LOG-1;k>=0;k--){
        if(depth_nodes[a] - (1<<k) >= depth_nodes[b]){
            a = up[a][k];
        }
    }
    if(a == b) return a;
    for(int k=LOG-1;k>=0;k--){
        if(up[a][k] != up[b][k]){
            a = up[a][k];
            b = up[b][k];
        }
    }
    return up[a][0];
}

// Priority Queue implementation with lazy deletion
typedef struct {
    int size;
    long long data[MAXM];
    long long removed[MAXM];
} MaxHeap;

void heap_init(MaxHeap* heap){
    heap->size = 0;
    memset(heap->removed, 0, sizeof(heap->removed));
}

void heap_push(MaxHeap* heap, long long val){
    heap->data[++heap->size] = val;
    int i = heap->size;
    while(i > 1 && heap->data[i] > heap->data[i/2]){
        long long tmp = heap->data[i];
        heap->data[i] = heap->data[i/2];
        heap->data[i/2] = tmp;
        i /= 2;
    }
}

void heap_remove(MaxHeap* heap, long long val){
    // Mark as removed
    heap->removed[val] = 1;
}

long long heap_top(MaxHeap* heap){
    while(heap->size > 0 && heap->removed[heap->data[1]]){
        heap->removed[heap->data[1]] = 0;
        heap->data[1] = heap->data[heap->size--];
        int i = 1;
        while(1){
            int largest = i;
            if(2*i <= heap->size && heap->data[2*i] > heap->data[largest]) largest = 2*i;
            if(2*i+1 <= heap->size && heap->data[2*i+1] > heap->data[largest]) largest = 2*i+1;
            if(largest != i){
                long long tmp = heap->data[i];
                heap->data[i] = heap->data[largest];
                heap->data[largest] = tmp;
                i = largest;
            }
            else break;
        }
    }
    if(heap->size == 0) return -1;
    return heap->data[1];
}

// Main
int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n-1;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    // Initialize LCA
    depth_nodes[1] = 0;
    dfs(1, 1);
    
    // Initialize heaps
    MaxHeap global_heap;
    heap_init(&global_heap);
    
    // To track requests
    typedef struct {
        int a, b, v;
    } Request;
    Request req[MAXM];
    memset(req, 0, sizeof(req));
    
    for(int i=1;i<=m;i++){
        int type;
        scanf("%d", &type);
        events[i].type = type;
        if(type == 0){
            scanf("%d %d %d", &events[i].a, &events[i].b, &events[i].val);
            req[i].a = events[i].a;
            req[i].b = events[i].b;
            req[i].v = events[i].val;
            heap_push(&global_heap, req[i].v);
        }
        else if(type ==1){
            scanf("%d", &events[i].t);
            // Not implemented
        }
        else if(type ==2){
            scanf("%d", &events[i].x);
            long long top = heap_top(&global_heap);
            printf("%lld\n", top);
        }
    }
    return 0;
}