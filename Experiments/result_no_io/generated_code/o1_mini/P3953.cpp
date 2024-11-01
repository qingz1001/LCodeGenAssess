#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Define maximum limits
#define MAXN 100005
#define MAXM 100005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to;
    int cost;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
Edge* adj_rev[MAXN];
int N, M;
long long K;
int P;

// Heap for Dijkstra
typedef struct HeapNode {
    int u;
    long long dist;
} HeapNode;

typedef struct Heap {
    HeapNode* data;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int capacity){
    Heap* heap = (Heap*)malloc(sizeof(Heap));
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

void heapify_up(Heap* heap, int idx){
    if(idx == 0) return;
    int parent = (idx -1)/2;
    if(heap->data[parent].dist > heap->data[idx].dist){
        swap(&heap->data[parent], &heap->data[idx]);
        heapify_up(heap, parent);
    }
}

void heapify_down(Heap* heap, int idx){
    int smallest = idx;
    int left = 2*idx +1;
    int right = 2*idx +2;
    if(left < heap->size && heap->data[left].dist < heap->data[smallest].dist){
        smallest = left;
    }
    if(right < heap->size && heap->data[right].dist < heap->data[smallest].dist){
        smallest = right;
    }
    if(smallest != idx){
        swap(&heap->data[smallest], &heap->data[idx]);
        heapify_down(heap, smallest);
    }
}

void pushHeap(Heap* heap, int u, long long dist){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode)*heap->capacity);
    }
    heap->data[heap->size].u = u;
    heap->data[heap->size].dist = dist;
    heapify_up(heap, heap->size);
    heap->size++;
}

HeapNode popHeap(Heap* heap){
    HeapNode top = heap->data[0];
    heap->data[0] = heap->data[heap->size -1];
    heap->size--;
    heapify_down(heap, 0);
    return top;
}

int isEmpty(Heap* heap){
    return heap->size ==0;
}

// Dijkstra
long long dist1[MAXN];
long long distN[MAXN];
void dijkstra(int start, long long* dist, Edge* adj_list[]){
    for(int i=1;i<=N;i++) dist[i]=INF;
    dist[start]=0;
    Heap* heap = createHeap(65536);
    pushHeap(heap, start, 0);
    while(!isEmpty(heap)){
        HeapNode current = popHeap(heap);
        int u = current.u;
        if(current.dist > dist[u]) continue;
        Edge* e = adj_list[u];
        while(e){
            int v = e->to;
            long long new_dist = dist[u] + e->cost;
            if(new_dist < dist[v]){
                dist[v] = new_dist;
                pushHeap(heap, v, new_dist);
            }
            e = e->next;
        }
    }
    free(heap->data);
    free(heap);
}

// BFS for reachability
int visited1[MAXN];
void dfs1(int u){
    visited1[u]=1;
    Edge* e = adj[u];
    while(e){
        if(!visited1[e->to]){
            dfs1(e->to);
        }
        e = e->next;
    }
}

int visitedN_rev[MAXN];
void dfsN(int u){
    visitedN_rev[u]=1;
    Edge* e = adj_rev[u];
    while(e){
        if(!visitedN_rev[e->to]){
            dfsN(e->to);
        }
        e = e->next;
    }
}

// Detect zero-weight cycle
int has_zero_cycle;
int in_stack[MAXN];
void dfs_cycle(int u, Edge* adj_list[]){
    if(has_zero_cycle) return;
    in_stack[u]=1;
    Edge* e = adj_list[u];
    while(e){
        if(e->cost ==0){
            if(!visited1[e->to] || !visitedN_rev[e->to]) { e = e->next; continue;}
            if(!in_stack[e->to]){
                dfs_cycle(e->to, adj_list);
                if(has_zero_cycle) return;
            }
            else{
                has_zero_cycle=1;
                return;
            }
        }
        e = e->next;
    }
    in_stack[u]=0;
}

long long dp[MAXN];
long long d;
long long result;

// Topological sort
int order[MAXN];
int idx_order;
int indegree[MAXN];
void topological_sort(int reachable){
    idx_order=0;
    memset(indegree, 0, sizeof(int)*(N+1));
    for(int u=1; u<=N; u++) {
        if(!reachable || (visited1[u] && visitedN_rev[u])){
            Edge* e = adj[u];
            while(e){
                if(!reachable || (visited1[e->to] && visitedN_rev[e->to])){
                    indegree[e->to]++;
                }
                e = e->next;
            }
        }
    }
    // Simple queue
    int* queue = (int*)malloc(sizeof(int)*(N+1));
    int front=0, back=0;
    for(int u=1; u<=N; u++) {
        if((!reachable || (visited1[u] && visitedN_rev[u])) && indegree[u]==0){
            queue[back++] = u;
        }
    }
    while(front < back){
        int u = queue[front++];
        order[idx_order++] = u;
        Edge* e = adj[u];
        while(e){
            if(!reachable || (visited1[e->to] && visitedN_rev[e->to])){
                indegree[e->to]--;
                if(indegree[e->to]==0){
                    queue[back++] = e->to;
                }
            }
            e = e->next;
        }
    }
    free(queue);
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%d %d %lld %d", &N, &M, &K, &P);
        for(int i=1;i<=N;i++) { adj[i]=NULL; adj_rev[i]=NULL;}
        for(int i=0;i<M;i++){
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            Edge* e = (Edge*)malloc(sizeof(Edge));
            e->to = b;
            e->cost = c;
            e->next = adj[a];
            adj[a] = e;
            // Reverse graph
            Edge* er = (Edge*)malloc(sizeof(Edge));
            er->to = a;
            er->cost = c;
            er->next = adj_rev[b];
            adj_rev[b] = er;
        }
        // Dijkstra from 1
        dijkstra(1, dist1, adj);
        // Dijkstra from N on reversed graph
        dijkstra(N, distN, adj_rev);
        long long shortest = dist1[N];
        // Find reachable nodes
        memset(visited1, 0, sizeof(int)*(N+1));
        dfs1(1);
        memset(visitedN_rev, 0, sizeof(int)*(N+1));
        dfsN(N);
        // Check for zero-weight cycle
        has_zero_cycle=0;
        memset(in_stack, 0, sizeof(int)*(N+1));
        for(int u=1; u<=N; u++) {
            if(visited1[u] && visitedN_rev[u]){
                Edge* e = adj[u];
                while(e){
                    if(e->cost ==0 && visited1[e->to] && visitedN_rev[e->to]){
                        if(!in_stack[e->to]){
                            dfs_cycle(e->to, adj);
                            if(has_zero_cycle) break;
                        }
                    }
                    e = e->next;
                }
                if(has_zero_cycle) break;
            }
        }
        if(has_zero_cycle){
            printf("-1\n");
            // Free memory
            for(int i=1;i<=N;i++){
                Edge* e = adj[i];
                while(e){
                    Edge* temp = e;
                    e = e->next;
                    free(temp);
                }
                Edge* er = adj_rev[i];
                while(er){
                    Edge* temp = er;
                    er = er->next;
                    free(temp);
                }
            }
            continue;
        }
        // If no zero-weight cycle, proceed to count paths
        // Use DP with topological order
        topological_sort(1);
        for(int i=0;i<=N;i++) dp[i]=0;
        dp[1]=1;
        for(int i=0;i<idx_order;i++){
            int u = order[i];
            Edge* e = adj[u];
            while(e){
                int v = e->to;
                if(dist1[u] + e->cost + distN[v] <= shortest + K){
                    dp[v] = (dp[v] + dp[u]) % P;
                }
                e = e->next;
            }
        }
        printf("%lld\n", dp[N]%P);
        // Free memory
        for(int i=1;i<=N;i++){
            Edge* e = adj[i];
            while(e){
                Edge* temp = e;
                e = e->next;
                free(temp);
            }
            Edge* er = adj_rev[i];
            while(er){
                Edge* temp = er;
                er = er->next;
                free(temp);
            }
        }
    }
    return 0;
}