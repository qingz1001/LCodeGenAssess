#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 50001
#define MAXK 20001
#define INF 1000000000
#define MAXM 50001
#define LOGK 15

typedef struct {
    int to;
    int cost;
    int d;
} Edge;

typedef struct {
    Edge edges[MAXM];
    int cnt;
} AdjList;

typedef struct {
    int u;
    int v;
    int w;
} DictEdge;

typedef struct {
    int node;
    int dict;
    int dist;
} State;

typedef struct {
    State *data;
    int size;
    int capacity;
} Heap;

Heap* create_heap(int capacity){
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (State*)malloc(sizeof(State)*capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(State *a, State *b){
    State temp = *a;
    *a = *b;
    *b = temp;
}

void heap_push(Heap *heap, State s){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (State*)realloc(heap->data, sizeof(State)*heap->capacity);
    }
    int i = heap->size++;
    heap->data[i] = s;
    while(i >0){
        int parent = (i-1)/2;
        if(heap->data[parent].dist <= heap->data[i].dist) break;
        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

State heap_pop(Heap *heap){
    State top = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    int i=0;
    while(1){
        int smallest = i;
        int l = 2*i+1, r=2*i+2;
        if(l < heap->size && heap->data[l].dist < heap->data[smallest].dist) smallest = l;
        if(r < heap->size && heap->data[r].dist < heap->data[smallest].dist) smallest = r;
        if(smallest == i) break;
        swap(&heap->data[i], &heap->data[smallest]);
        i = smallest;
    }
    return top;
}

int up_table[MAXK][LOGK];
int depth_dk[MAXK];
AdjList dict_adj[MAXK];
AdjList graph[MAXN];
int n_nodes, m_edges, k_nodes;
DictEdge dict_edges_tmp[MAXK];
int LOG;

int lca(int u, int v){
    if(depth_dk[u] < depth_dk[v]){
        int temp = u; u = v; v = temp;
    }
    for(int i=LOG-1;i>=0;i--){
        if(depth_dk[u] - (1<<i) >= depth_dk[v]){
            u = up_table[u][i];
        }
    }
    if(u == v) return u;
    for(int i=LOG-1;i>=0;i--){
        if(up_table[u][i] != -1 && up_table[u][i] != up_table[v][i]){
            u = up_table[u][i];
            v = up_table[v][i];
        }
    }
    return up_table[u][0];
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        // Read n, m, k
        scanf("%d %d %d", &n_nodes, &m_edges, &k_nodes);
        // Initialize graph
        for(int i=1;i<=n_nodes;i++) graph[i].cnt=0;
        // Read m edges
        for(int i=0;i<m_edges;i++){
            int a, b, c, d;
            scanf("%d %d %d %d", &a, &b, &c, &d);
            graph[a].edges[graph[a].cnt].to = b;
            graph[a].edges[graph[a].cnt].cost = c;
            graph[a].edges[graph[a].cnt].d = d;
            graph[a].cnt++;
        }
        // Read k-1 dict edges
        for(int i=1;i<k_nodes;i++){
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            dict_adj[u].edges[dict_adj[u].cnt].to = v;
            dict_adj[u].edges[dict_adj[u].cnt].cost = w; // w is not used
            dict_adj[u].cnt++;
        }
        // Initialize for LCA
        for(int i=1;i<=k_nodes;i++) {
            for(int j=0;j<LOGK;j++) up_table[i][j]=-1;
            depth_dk[i]=0;
        }
        // BFS to set up_table and depth
        int queue_k[MAXK];
        int front=0, rear=0;
        queue_k[rear++] =1;
        up_table[1][0]=-1;
        depth_dk[1]=0;
        while(front < rear){
            int u = queue_k[front++];
            for(int i=0;i<dict_adj[u].cnt;i++){
                int v = dict_adj[u].edges[i].to;
                up_table[v][0] = u;
                depth_dk[v] = depth_dk[u]+1;
                queue_k[rear++] = v;
            }
        }
        // Build up_table
        LOG =0;
        while((1<<LOG) <=k_nodes) LOG++;
        for(int j=1;j<LOG;j++){
            for(int i=1;i<=k_nodes;i++){
                if(up_table[i][j-1] != -1){
                    up_table[i][j] = up_table[ up_table[i][j-1] ][j-1];
                }
                else{
                    up_table[i][j] = -1;
                }
            }
        }
        // Initialize distances
        // Assuming n_nodes * k_nodes <= 2000000
        int total_states = n_nodes * k_nodes +2;
        int *dist = (int*)malloc(sizeof(int)*(n_nodes+1)*(k_nodes+1));
        for(int i=0;i<=n_nodes;i++){
            for(int j=0;j<=k_nodes;j++) dist[i*(k_nodes+1)+j] = INF;
        }
        // Initialize heap
        Heap *heap = create_heap(1000000);
        // Starting state: node 1, dict 1, dist 0
        dist[1*(k_nodes+1)+1] =0;
        State start;
        start.node =1;
        start.dict =1;
        start.dist =0;
        heap_push(heap, start);
        // Dijkstra
        while(heap->size >0){
            State current = heap_pop(heap);
            if(current.dist > dist[current.node*(k_nodes+1)+current.dict]) continue;
            for(int i=0;i<graph[current.node].cnt;i++){
                int to = graph[current.node].edges[i].to;
                int cost_e = graph[current.node].edges[i].cost;
                int d_e = graph[current.node].edges[i].d;
                // Compute LCA
                int lca_node = lca(current.dict, d_e);
                int lcp = depth_dk[lca_node];
                int new_dist = current.dist + cost_e + lcp;
                if(new_dist < dist[to*(k_nodes+1)+d_e]){
                    dist[to*(k_nodes+1)+d_e] = new_dist;
                    State next;
                    next.node = to;
                    next.dict = d_e;
                    next.dist = new_dist;
                    heap_push(heap, next);
                }
            }
        }
        // For nodes 2 to n, find min distance
        for(int i=2;i<=n_nodes;i++){
            int min_dist = INF;
            for(int j=1;j<=k_nodes;j++) {
                if(dist[i*(k_nodes+1)+j] < min_dist) min_dist = dist[i*(k_nodes+1)+j];
            }
            printf("%d\n", min_dist);
        }
        // Free
        free(dist);
        free(heap->data);
        free(heap);
    }
}