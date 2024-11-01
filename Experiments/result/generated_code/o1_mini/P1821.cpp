#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001
#define MAXM 200001
#define INF 1000000000

typedef struct {
    int to;
    int w;
    int next;
} Edge;

Edge orig_edges[MAXM];
int head_orig[MAXN];
int orig_edge_cnt = 0;

Edge rev_edges[MAXM];
int head_rev[MAXN];
int rev_edge_cnt = 0;

// Heap structure
typedef struct {
    int node;
    int dist;
} HeapNode;

typedef struct {
    HeapNode data[MAXN + 1];
    int size;
} Heap;

// Swap two heap nodes
void swap_heap(HeapNode *a, HeapNode *b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Initialize heap
void heap_init(Heap *h){
    h->size = 0;
}

// Push a node into the heap
void heap_push(Heap *h, int node, int dist){
    int i = ++(h->size);
    h->data[i].node = node;
    h->data[i].dist = dist;
    while(i > 1 && h->data[i].dist < h->data[i/2].dist){
        swap_heap(&h->data[i], &h->data[i/2]);
        i /= 2;
    }
}

// Pop the top node from the heap
HeapNode heap_pop(Heap *h){
    HeapNode top = h->data[1];
    HeapNode last = h->data[h->size--];
    int i = 1, child;
    while(i * 2 <= h->size){
        child = i * 2;
        if(child < h->size && h->data[child+1].dist < h->data[child].dist){
            child++;
        }
        if(last.dist <= h->data[child].dist){
            break;
        }
        h->data[i] = h->data[child];
        i = child;
    }
    h->data[i] = last;
    return top;
}

// Check if heap is empty
int heap_empty(Heap *h){
    return h->size == 0;
}

// Dijkstra's algorithm
void dijkstra(int n, Edge edges[], int head[], int src, int *dist){
    for(int i=1;i<=n;i++) dist[i] = INF;
    dist[src] = 0;
    Heap h;
    heap_init(&h);
    heap_push(&h, src, 0);
    while(!heap_empty(&h)){
        HeapNode current = heap_pop(&h);
        int u = current.node;
        int d = current.dist;
        if(d > dist[u]) continue;
        for(int e = head[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            int w = edges[e].w;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                heap_push(&h, v, dist[v]);
            }
        }
    }
}

int main(){
    int n, m, x;
    scanf("%d %d %d", &n, &m, &x);
    memset(head_orig, -1, sizeof(head_orig));
    memset(head_rev, -1, sizeof(head_rev));
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        orig_edges[orig_edge_cnt].to = v;
        orig_edges[orig_edge_cnt].w = w;
        orig_edges[orig_edge_cnt].next = head_orig[u];
        head_orig[u] = orig_edge_cnt++;
        
        rev_edges[rev_edge_cnt].to = u;
        rev_edges[rev_edge_cnt].w = w;
        rev_edges[rev_edge_cnt].next = head_rev[v];
        head_rev[v] = rev_edge_cnt++;
    }
    int dist_to_x[MAXN];
    dijkstra(n, rev_edges, head_rev, x, dist_to_x);
    int dist_from_x[MAXN];
    dijkstra(n, orig_edges, head_orig, x, dist_from_x);
    int max_total = 0;
    for(int i=1;i<=n;i++){
        if(dist_to_x[i] + dist_from_x[i] > max_total){
            max_total = dist_to_x[i] + dist_from_x[i];
        }
    }
    printf("%d\n", max_total);
    return 0;
}