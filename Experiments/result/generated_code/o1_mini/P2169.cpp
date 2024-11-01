#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int u, v, w;
} Edge;

int cmp(const void *a, const void *b){
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    if(ea->u != eb->u)
        return ea->u - eb->u;
    if(ea->v != eb->v)
        return ea->v - eb->v;
    return ea->w - eb->w;
}

typedef struct {
    int node;
    int cost;
} PQNode;

typedef struct {
    PQNode *data;
    int size;
    int capacity;
} PriorityQueue;

void initPQ(PriorityQueue *pq, int cap){
    pq->data = (PQNode*)malloc(sizeof(PQNode)*cap);
    pq->size = 0;
    pq->capacity = cap;
}

void swap(PQNode *a, PQNode *b){
    PQNode temp = *a;
    *a = *b;
    *b = temp;
}

void pushPQ(PriorityQueue *pq, PQNode node){
    if(pq->size == pq->capacity){
        pq->capacity *= 2;
        pq->data = (PQNode*)realloc(pq->data, sizeof(PQNode)*pq->capacity);
    }
    pq->data[pq->size] = node;
    int i = pq->size;
    pq->size++;
    while(i > 0){
        int parent = (i-1)/2;
        if(pq->data[parent].cost > pq->data[i].cost){
            swap(&pq->data[parent], &pq->data[i]);
            i = parent;
        }
        else break;
    }
}

PQNode popPQ(PriorityQueue *pq){
    PQNode top = pq->data[0];
    pq->size--;
    pq->data[0] = pq->data[pq->size];
    int i = 0;
    while(1){
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;
        if(left < pq->size && pq->data[left].cost < pq->data[smallest].cost)
            smallest = left;
        if(right < pq->size && pq->data[right].cost < pq->data[smallest].cost)
            smallest = right;
        if(smallest != i){
            swap(&pq->data[i], &pq->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Edge *edges = (Edge*)malloc(sizeof(Edge)*m);
    for(int i=0;i<m;i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    qsort(edges, m, sizeof(Edge), cmp);
    // Build adjacency lists
    // First, create sorted outgoing lists
    int *start = (int*)calloc(n+2, sizeof(int));
    for(int i=0;i<m;i++)
        start[edges[i].u]++;
    for(int i=1;i<=n;i++)
        start[i] += start[i-1];
    int *out = (int*)malloc(sizeof(int)*m);
    int *wout = (int*)malloc(sizeof(int)*m);
    for(int i=0;i<m;i++){
        int u = edges[i].u;
        int pos = start[u-1] + i - (start[u-1]);
        out[start[u-1]] = edges[i].v;
        wout[start[u-1]] = edges[i].w;
        start[u-1]++;
    }
    // Reset start
    for(int i=n;i>=1;i--)
        start[i] = start[i-1];
    start[0] = 0;
    // Now, sort by u then v is already sorted
    // Build adjacency list considering bidirectional edges
    // Use temporary arrays
    int *head_adj = (int*)calloc(n+1, sizeof(int));
    int total = 0;
    for(int i=0;i<m;i++){
        head_adj[edges[i].u]++;
    }
    // First pass to count bidirectional edges
    int bidir = 0;
    for(int i=0;i<m;i++){
        // Binary search for reverse edge
        int u = edges[i].u;
        int v = edges[i].v;
        // Binary search in edges for v->u
        int left = 0, right = m-1, found = 0;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(edges[mid].u < v){
                left = mid +1;
            }
            else if(edges[mid].u > v){
                right = mid -1;
            }
            else{
                if(edges[mid].v < u){
                    left = mid +1;
                }
                else if(edges[mid].v > u){
                    right = mid -1;
                }
                else{
                    found =1;
                    break;
                }
            }
        }
        if(found && u < v){
            // This pair will have bidirectional zero edges
            bidir++;
        }
    }
    // Calculate total edges
    int total_edges = m + bidir; // Each bidirectional adds one extra
    // Allocate adjacency list
    int *adj_to = (int*)malloc(sizeof(int)*(2*m));
    int *adj_cost = (int*)malloc(sizeof(int)*(2*m));
    int *adj_head = (int*)(calloc(n+1, sizeof(int)));
    // Populate adjacency list
    // First pass to count
    for(int i=0;i<m;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        // Binary search for v->u
        int left = 0, right = m-1, found = 0;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(edges[mid].u < v){
                left = mid +1;
            }
            else if(edges[mid].u > v){
                right = mid -1;
            }
            else{
                if(edges[mid].v < u){
                    left = mid +1;
                }
                else if(edges[mid].v > u){
                    right = mid -1;
                }
                else{
                    found =1;
                    break;
                }
            }
        }
        if(found){
            if(u < v){
                adj_head[u]++;
                adj_head[v]++;
            }
        }
        else{
            adj_head[u]++;
        }
    }
    // Prefix sum to get starting indices
    for(int i=1;i<=n;i++)
        adj_head[i] += adj_head[i-1];
    int *current = (int*)malloc(sizeof(int)*(n+1));
    memcpy(current, adj_head, sizeof(int)*(n+1));
    for(int i=0;i<m;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        // Binary search for v->u
        int left = 0, right = m-1, found = 0;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(edges[mid].u < v){
                left = mid +1;
            }
            else if(edges[mid].u > v){
                right = mid -1;
            }
            else{
                if(edges[mid].v < u){
                    left = mid +1;
                }
                else if(edges[mid].v > u){
                    right = mid -1;
                }
                else{
                    found =1;
                    break;
                }
            }
        }
        if(found){
            if(u < v){
                adj_to[current[u]++] = v;
                adj_cost[current[u]-1] = 0;
                adj_to[current[v]++] = u;
                adj_cost[current[v]-1] = 0;
            }
        }
        else{
            adj_to[current[u]++] = v;
            adj_cost[current[u]-1] = edges[i].w;
        }
    }
    // Free memory
    free(edges);
    free(out);
    free(wout);
    free(start);
    // Dijkstra
    int *dist = (int*)malloc(sizeof(int)*(n+1));
    for(int i=1;i<=n;i++)
        dist[i] = INT32_MAX;
    dist[1] = 0;
    PriorityQueue pq;
    initPQ(&pq, 1<<20);
    PQNode start_node = {1, 0};
    pushPQ(&pq, start_node);
    while(pq.size >0){
        PQNode current_node = popPQ(&pq);
        int u = current_node.node;
        int d = current_node.cost;
        if(u == n){
            break;
        }
        if(d > dist[u])
            continue;
        // Iterate through adjacency list
        int start_idx = adj_head[u-1];
        int end_idx = adj_head[u];
        for(int i=start_idx;i<end_idx;i++){
            int v = adj_to[i];
            int w = adj_cost[i];
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                PQNode new_node = {v, dist[v]};
                pushPQ(&pq, new_node);
            }
        }
    }
    printf("%d\n", dist[n]);
    // Free memory
    free(adj_to);
    free(adj_cost);
    free(adj_head);
    free(current);
    free(dist);
    free(pq.data);
    return 0;
}