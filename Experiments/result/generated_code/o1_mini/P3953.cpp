#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>

// Define constants
#define INF 0x3f3f3f3f

// Structure for edges
typedef struct Edge {
    int to;
    int cost;
    struct Edge* next;
} Edge;

// Priority Queue for Dijkstra
typedef struct {
    int *heap;
    int *pos;
    int size;
    int capacity;
} PriorityQueue;

// Initialize priority queue
PriorityQueue* initPQ(int capacity){
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->heap = (int*)malloc(sizeof(int)*(capacity+1));
    pq->pos = (int*)malloc(sizeof(int)*(capacity+1));
    pq->size = 0;
    pq->capacity = capacity;
    for(int i=0;i<=capacity;i++) pq->pos[i] = 0;
    return pq;
}

// Swap elements in heap
void swap(PriorityQueue* pq, int i, int j){
    int temp = pq->heap[i];
    pq->heap[i] = pq->heap[j];
    pq->heap[j] = temp;
    pq->pos[pq->heap[i]] = i;
    pq->pos[pq->heap[j]] = j;
}

// Push to priority queue
void pushPQ(PriorityQueue* pq, int node){
    pq->size++;
    pq->heap[pq->size] = node;
    pq->pos[node] = pq->size;
    int current = pq->size;
    while(current >1 && pq->heap[current] < pq->heap[current/2]){
        swap(pq, current, current/2);
        current /=2;
    }
}

// Pop from priority queue
int popPQ(PriorityQueue* pq){
    if(pq->size ==0) return -1;
    int top = pq->heap[1];
    pq->heap[1] = pq->heap[pq->size];
    pq->pos[pq->heap[1]] =1;
    pq->size--;
    int current =1;
    while(current*2 <= pq->size){
        int smallest = current;
        if(pq->heap[current*2] < pq->heap[smallest]) smallest = current*2;
        if(current*2+1 <= pq->size && pq->heap[current*2+1] < pq->heap[smallest]) smallest = current*2+1;
        if(smallest != current){
            swap(pq, current, smallest);
            current = smallest;
        }
        else break;
    }
    return top;
}

// Free priority queue
void freePQ(PriorityQueue* pq){
    free(pq->heap);
    free(pq->pos);
    free(pq);
}

// Main
int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int N, M, K;
        long long P;
        scanf("%d %d %d %lld", &N, &M, &K, &P);
        // Initialize adjacency lists
        Edge** adj = (Edge**)malloc((N+1)*sizeof(Edge*));
        Edge** adj_rev = (Edge**)malloc((N+1)*sizeof(Edge*));
        for(int i=1;i<=N;i++) { adj[i]=NULL; adj_rev[i]=NULL;}
        // Read edges
        int a, b, c;
        for(int i=0;i<M;i++){
            scanf("%d %d %d", &a, &b, &c);
            Edge* e = (Edge*)malloc(sizeof(Edge));
            e->to = b;
            e->cost = c;
            e->next = adj[a];
            adj[a] = e;
            // Reverse edge for reverse graph
            Edge* er = (Edge*)malloc(sizeof(Edge));
            er->to = a;
            er->cost = c;
            er->next = adj_rev[b];
            adj_rev[b] = er;
        }
        // Dijkstra from 1
        int* d1 = (int*)malloc((N+1)*sizeof(int));
        for(int i=1;i<=N;i++) d1[i]=INF;
        d1[1]=0;
        PriorityQueue* pq = initPQ(N);
        pushPQ(pq, 1);
        while(pq->size >0){
            int u = popPQ(pq);
            Edge* e = adj[u];
            while(e){
                if(d1[e->to] > d1[u] + e->cost){
                    d1[e->to] = d1[u] + e->cost;
                    pushPQ(pq, e->to);
                }
                e = e->next;
            }
        }
        freePQ(pq);
        // If N is unreachable, though problem states at least one path exists
        // Dijkstra from N on reverse graph
        int* d2 = (int*)malloc((N+1)*sizeof(int));
        for(int i=1;i<=N;i++) d2[i]=INF;
        d2[N]=0;
        pq = initPQ(N);
        pushPQ(pq, N);
        while(pq->size >0){
            int u = popPQ(pq);
            Edge* e = adj_rev[u];
            while(e){
                if(d2[e->to] > d2[u] + e->cost){
                    d2[e->to] = d2[u] + e->cost;
                    pushPQ(pq, e->to);
                }
                e = e->next;
            }
        }
        freePQ(pq);
        // Shortest distance
        int d = d1[N];
        // Find reachable nodes from 1 and to N
        bool* reachable = (bool*)calloc(N+1, sizeof(bool));
        for(int i=1;i<=N;i++) {
            if(d1[i] < INF && d2[i] < INF){
                reachable[i] = true;
            }
        }
        // Find SCCs using Kosaraju
        // First pass: order
        int* order = (int*)malloc((N+1)*sizeof(int));
        int top =0;
        bool* visited = (bool*)calloc(N+1, sizeof(bool));
        // DFS on original graph
        void dfs1(int u){
            visited[u]=true;
            Edge* e = adj[u];
            while(e){
                if(reachable[e->to] && !visited[e->to]){
                    dfs1(e->to);
                }
                e = e->next;
            }
            order[++top] = u;
        }
        for(int i=1;i<=N;i++) {
            if(reachable[i] && !visited[i]){
                dfs1(i);
            }
        }
        // Second pass: assign components
        int* comp = (int*)malloc((N+1)*sizeof(int));
        int num_comp =0;
        memset(visited, 0, sizeof(bool)*(N+1));
        void dfs2(int u, int label){
            comp[u] = label;
            visited[u]=true;
            Edge* e = adj_rev[u];
            while(e){
                if(reachable[e->to] && !visited[e->to]){
                    dfs2(e->to, label);
                }
                e = e->next;
            }
        }
        for(int i=top;i>=1;i--){
            int u = order[i];
            if(reachable[u] && !visited[u]){
                num_comp++;
                dfs2(u, num_comp);
            }
        }
        // Check for zero-weight cycles
        bool has_zero_cycle = false;
        // Count size of each component
        int* size_comp = (int*)calloc(num_comp+1, sizeof(int));
        for(int i=1;i<=N;i++) {
            if(reachable[i]){
                size_comp[comp[i]]++;
            }
        }
        // For each edge, check if it is within the same component and has c=0
        // Also check if component size >1
        for(int i=1;i<=N;i++) {
            if(reachable[i]){
                Edge* e = adj[i];
                while(e){
                    if(reachable[e->to] && comp[i]==comp[e->to]){
                        if(e->cost !=0){
                            // Not zero-weight edge
                        }
                        else{
                            if(size_comp[comp[i]] >1){
                                has_zero_cycle = true;
                                break;
                            }
                        }
                    }
                    e = e->next;
                }
                if(has_zero_cycle) break;
            }
        }
        // Free memory
        free(order);
        free(visited);
        free(size_comp);
        free(comp);
        // If has zero-weight cycle, output -1
        if(has_zero_cycle){
            printf("-1\n");
        }
        else{
            // Count the number of paths from 1 to N with total distance <= d + K
            // Since no zero-weight cycles, we can use DP sorted by distance
            // Initialize DP
            // Find nodes sorted by d1
            int* nodes = (int*)malloc((N+1)*sizeof(int));
            for(int i=1;i<=N;i++) nodes[i] =i;
            // Simple insertion sort based on d1
            // Not efficient for N=1e5, use counting sort since d1[i] <= 1e8
            // But d1[i] can be up to 1e8, which is too large
            // Instead, use a list of nodes sorted by d1 using a Schwartzian transform
            // Implement a simple sort using qsort
            int compare(const void* a, const void* b){
                int u = *(int*)a;
                int v = *(int*)b;
                if(d1[u] != d1[v]) return d1[u] - d1[v];
                return u - v;
            }
            qsort(nodes+1, N, sizeof(int), compare);
            // Initialize dp
            unsigned long long* dp = (unsigned long long*)calloc(N+1, sizeof(unsigned long long));
            dp[1] =1;
            // Iterate over nodes in sorted order
            for(int i=1;i<=N;i++){
                int u = nodes[i];
                if(dp[u]==0) continue;
                Edge* e = adj[u];
                while(e){
                    if(reachable[e->to]){
                        if(d1[u] + e->cost + d2[e->to] <= d + K){
                            dp[e->to] = (dp[e->to] + dp[u]) % P;
                        }
                    }
                    e = e->next;
                }
            }
            printf("%llu\n", dp[N]%P);
            // Free memory
            free(nodes);
            free(dp);
        }
        // Free adjacency lists
        for(int i=1;i<=N;i++){
            Edge* e = adj[i];
            while(e){
                Edge* tmp = e;
                e = e->next;
                free(tmp);
            }
            e = adj_rev[i];
            while(e){
                Edge* tmp = e;
                e = e->next;
                free(tmp);
            }
        }
        free(adj);
        free(adj_rev);
        free(d1);
        free(d2);
    }
}