#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MAX_M 100000
#define MAX_ADJ 200000
#define INF 1000000000

typedef struct {
    int to;
    long t;
} Edge;

// Adjacency list
Edge adj_edges[MAX_ADJ];
int adj_ptr[MAX_N]; // Points to the start of each node's adjacency list
int edge_index_mat[MAX_N][MAX_N];
int edge_deleted[MAX_M];

// Heap structure
typedef struct {
    int size;
    int nodes[MAX_N];
    long dist[MAX_N];
} Heap;

void heap_init(Heap *heap) {
    heap->size = 0;
}

void heap_push_heap(Heap *heap, int node, long distance) {
    int i = ++(heap->size);
    heap->nodes[i] = node;
    heap->dist[i] = distance;
    // Sift up
    while(i > 1){
        int parent = i / 2;
        if(heap->dist[parent] <= heap->dist[i]) break;
        // Swap
        int tmp_node = heap->nodes[parent];
        long tmp_dist = heap->dist[parent];
        heap->nodes[parent] = heap->nodes[i];
        heap->dist[parent] = heap->dist[i];
        heap->nodes[i] = tmp_node;
        heap->dist[i] = tmp_dist;
        i = parent;
    }
}

int heap_pop_min(Heap *heap, long *min_dist) {
    if(heap->size == 0) return -1;
    int min_node = heap->nodes[1];
    *min_dist = heap->dist[1];
    heap->nodes[1] = heap->nodes[heap->size];
    heap->dist[1] = heap->dist[heap->size];
    heap->size--;
    // Sift down
    int i = 1;
    while(2*i <= heap->size){
        int left = 2*i;
        int right = 2*i + 1;
        int smallest = left;
        if(right <= heap->size && heap->dist[right] < heap->dist[left]){
            smallest = right;
        }
        if(heap->dist[i] <= heap->dist[smallest]) break;
        // Swap
        int tmp_node = heap->nodes[i];
        long tmp_dist = heap->dist[i];
        heap->nodes[i] = heap->nodes[smallest];
        heap->dist[i] = heap->dist[smallest];
        heap->nodes[smallest] = tmp_node;
        heap->dist[smallest] = tmp_dist;
        i = smallest;
    }
    return min_node;
}

int main(){
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    // Initialize adjacency pointers
    memset(adj_ptr, 0, sizeof(adj_ptr));
    memset(edge_index_mat, -1, sizeof(edge_index_mat));
    // Read edges
    for(int edge_id=0; edge_id<m; edge_id++){
        int u, v;
        long t;
        scanf("%d %d %ld", &u, &v, &t);
        adj_edges[edge_id].to = v;
        adj_edges[edge_id].t = t;
        adj_ptr[u]++;
        adj_edges[m + edge_id].to = u;
        adj_edges[m + edge_id].t = t;
        adj_ptr[v]++;
        edge_index_mat[u][v] = edge_id;
        edge_index_mat[v][u] = edge_id;
    }
    // Reset adj_ptr to actual indices
    int temp_ptr[MAX_N];
    memcpy(temp_ptr, adj_ptr, sizeof(adj_ptr));
    memset(adj_ptr, 0, sizeof(adj_ptr));
    for(int edge_id=0; edge_id<m; edge_id++){
        int u, v;
        u = adj_edges[edge_id].to;
        v = adj_edges[m + edge_id].to;
        adj_edges[adj_ptr[u]] = (Edge){v, adj_edges[m + edge_id].t};
        adj_ptr[u]++;
        adj_edges[adj_ptr[v]] = (Edge){u, adj_edges[edge_id].t};
        adj_ptr[v]++;
    }
    // Initialize edge_deleted to 0
    memset(edge_deleted, 0, sizeof(edge_deleted));
    // Prepare for queries
    int current_mark = 0;
    int visit[MAX_N];
    long dist_store[MAX_N];
    Heap heap;
    heap_init(&heap);
    while(q--){
        int k, u, v;
        scanf("%d %d %d", &k, &u, &v);
        if(k == 1){
            // Query: find minimal maximum t path from u to v
            current_mark++;
            // Initialize
            for(int i=1;i<=n;i++) {
                visit[i] = 0;
                dist_store[i] = INF;
            }
            dist_store[u] = 0;
            visit[u] = current_mark;
            heap_init(&heap);
            heap_push_heap(&heap, u, 0);
            long result = INF;
            while(heap.size > 0){
                long min_dist;
                int node = heap_pop_min(&heap, &min_dist);
                if(node == v){
                    result = min_dist;
                    break;
                }
                if(min_dist > dist_store[node]) continue;
                for(int e=0; e<adj_ptr[node]; e++){
                    int neighbor = adj_edges[e].to;
                    long edge_t = adj_edges[e].t;
                    int edge_id = edge_index_mat[node][neighbor];
                    if(edge_id == -1 || edge_deleted[edge_id]) continue;
                    long new_dist = (dist_store[node] > edge_t) ? dist_store[node] : edge_t;
                    if(!visit[neighbor] || new_dist < dist_store[neighbor]){
                        dist_store[neighbor] = new_dist;
                        visit[neighbor] = current_mark;
                        heap_push_heap(&heap, neighbor, new_dist);
                    }
                }
            }
            printf("%ld\n", result);
        }
        else{
            // Delete operation: remove edge u-v
            int edge_id = edge_index_mat[u][v];
            if(edge_id != -1){
                edge_deleted[edge_id] = 1;
            }
        }
    }
    return 0;
}