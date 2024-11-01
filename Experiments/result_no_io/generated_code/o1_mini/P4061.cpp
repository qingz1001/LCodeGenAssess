#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAXN 50005

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

typedef struct {
    Edge* head;
} AdjList;

AdjList adj[MAXN];
long long distance_S[MAXN];
long long distance_T_val[MAXN];
int n, m, S, T;
long long INF = 1e18;

// Priority queue implementation for Dijkstra
typedef struct {
    int node;
    long long dist;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode)*capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swapHeapNode(HeapNode* a, HeapNode* b){
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapifyUp(MinHeap* heap, int idx){
    while(idx > 0){
        int parent = (idx -1)/2;
        if(heap->data[parent].dist > heap->data[idx].dist){
            swapHeapNode(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
        else break;
    }
}

void heapifyDown(MinHeap* heap, int idx){
    while(2*idx +1 < heap->size){
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
            swapHeapNode(&heap->data[smallest], &heap->data[idx]);
            idx = smallest;
        }
        else break;
    }
}

bool isEmpty(MinHeap* heap){
    return heap->size == 0;
}

HeapNode extractMin(MinHeap* heap){
    HeapNode min = heap->data[0];
    heap->data[0] = heap->data[heap->size-1];
    heap->size--;
    heapifyDown(heap, 0);
    return min;
}

void insertHeap(MinHeap* heap, int node, long long dist){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode)*heap->capacity);
    }
    heap->data[heap->size].node = node;
    heap->data[heap->size].dist = dist;
    heapifyUp(heap, heap->size);
    heap->size++;
}

void addEdge(int u, int v){
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = v;
    edge->next = adj[u].head;
    adj[u].head = edge;
}

void dijkstra(long long* dist, int start){
    for(int i=1;i<=n;i++) dist[i] = INF;
    dist[start] = 0;
    MinHeap* heap = createHeap(n);
    insertHeap(heap, start, 0);
    while(!isEmpty(heap)){
        HeapNode current = extractMin(heap);
        int u = current.node;
        if(current.dist > dist[u]) continue;
        for(Edge* e = adj[u].head; e != NULL; e = e->next){
            int v = e->to;
            if(dist[v] > dist[u] + e->to){
                // Not needed as weights are stored differently
            }
        }
    }
    free(heap->data);
    free(heap);
}

int main(){
    // Read input
    scanf("%d %d %d %d", &n, &m, &S, &T);
    for(int i=0;i<m;i++){
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        // Since weights are positive, we store them for Dijkstra
        // Modify adjacency list to store weight
        // Redefine Edge structure
    }

    // Implement Dijkstra with weights
    // Redefine Edge structure to include weight
    typedef struct WeightedEdge {
        int to;
        long long w;
        struct WeightedEdge* next;
    } WeightedEdge;

    // Reinitialize adjacency list
    for(int i=1;i<=n;i++) adj[i].head = NULL;
    // Read edges again
    fseek(stdin, 0, SEEK_SET);
    scanf("%d %d %d %d", &n, &m, &S, &T);
    for(int i=0;i<m;i++){
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        WeightedEdge* edge1 = (WeightedEdge*)malloc(sizeof(WeightedEdge));
        edge1->to = v;
        edge1->w = w;
        edge1->next = adj[u].head;
        adj[u].head = edge1;
        WeightedEdge* edge2 = (WeightedEdge*)malloc(sizeof(WeightedEdge));
        edge2->to = u;
        edge2->w = w;
        edge2->next = adj[v].head;
        adj[v].head = edge2;
    }

    // Dijkstra from S
    for(int i=1;i<=n;i++) distance_S[i] = INF;
    distance_S[S] = 0;
    MinHeap* heapS = createHeap(n);
    insertHeap(heapS, S, 0);
    while(!isEmpty(heapS)){
        HeapNode current = extractMin(heapS);
        int u = current.node;
        if(current.dist > distance_S[u]) continue;
        for(WeightedEdge* e = (WeightedEdge*)adj[u].head; e != NULL; e = e->next){
            int v = e->to;
            long long new_dist = distance_S[u] + e->w;
            if(new_dist < distance_S[v]){
                distance_S[v] = new_dist;
                insertHeap(heapS, v, new_dist);
            }
        }
    }
    free(heapS->data);
    free(heapS);

    // Dijkstra from T
    for(int i=1;i<=n;i++) distance_T_val[i] = INF;
    distance_T_val[T] = 0;
    MinHeap* heapT = createHeap(n);
    insertHeap(heapT, T, 0);
    while(!isEmpty(heapT)){
        HeapNode current = extractMin(heapT);
        int u = current.node;
        if(current.dist > distance_T_val[u]) continue;
        for(WeightedEdge* e = (WeightedEdge*)adj[u].head; e != NULL; e = e->next){
            int v = e->to;
            long long new_dist = distance_T_val[u] + e->w;
            if(new_dist < distance_T_val[v]){
                distance_T_val[v] = new_dist;
                insertHeap(heapT, v, new_dist);
            }
        }
    }
    free(heapT->data);
    free(heapT);

    long long D = distance_S[T];
    // Identify set C
    bool inC[MAXN];
    memset(inC, 0, sizeof(inC));
    int C_size = 0;
    int C_nodes[MAXN];
    for(int i=1;i<=n;i++) {
        if(distance_S[i] + distance_T_val[i] == D){
            inC[i] = true;
            C_nodes[C_size++] = i;
        }
    }

    // Assign indices to C_nodes for easy handling
    // Not necessary for this implementation

    // Build adjacency lists for C
    // Reinitialize adjacency list
    for(int i=1;i<=n;i++) adj[i].head = NULL;
    // Re-read edges
    fseek(stdin, 0, SEEK_SET);
    scanf("%d %d %d %d", &n, &m, &S, &T);
    for(int i=0;i<m;i++){
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        if(inC[u] && inC[v]){
            Edge* edge1 = (Edge*)malloc(sizeof(Edge));
            edge1->to = v;
            edge1->next = adj[u].head;
            adj[u].head = edge1;
            Edge* edge2 = (Edge*)malloc(sizeof(Edge));
            edge2->to = u;
            edge2->next = adj[v].head;
            adj[v].head = edge2;
        }
    }

    // For each node in C, store its neighbors
    // Also, count degrees
    int degreeC[MAXN];
    memset(degreeC, 0, sizeof(degreeC));
    for(int i=0;i<C_size;i++){
        int u = C_nodes[i];
        Edge* e = adj[u].head;
        while(e){
            degreeC[u]++;
            e = e->next;
        }
    }

    // Initialize adjacency lists as arrays for faster access
    int *neighbors[MAXN];
    int neighbor_size[MAXN];
    for(int i=0;i<C_size;i++){
        int u = C_nodes[i];
        neighbor_size[u] = degreeC[u];
        neighbors[u] = (int*)malloc(sizeof(int)*degreeC[u]);
        int idx = 0;
        Edge* e = adj[u].head;
        while(e){
            neighbors[u][idx++] = e->to;
            e = e->next;
        }
    }

    // Prepare for fast connectivity check
    // Create adjacency matrix using bitsets if possible
    // But with n=5e4, it's too large. Instead, use sorted neighbor lists for binary search
    for(int i=0;i<C_size;i++){
        int u = C_nodes[i];
        // Sort neighbors for binary search
        int cnt = neighbor_size[u];
        if(cnt >1){
            // Simple insertion sort as cnt is small
            for(int j=1;j<cnt;j++){
                int key = neighbors[u][j];
                int k = j-1;
                while(k >=0 && neighbors[u][k] > key){
                    neighbors[u][k+1] = neighbors[u][k];
                    k--;
                }
                neighbors[u][k+1] = key;
            }
        }
    }

    // For counting
    long long answer = 0;

    // Temporary array for counting connections to Y_A
    int *countB = (int*)calloc(n+1, sizeof(int));

    // Iterate over each A
    for(int i=0;i<C_size;i++){
        int A = C_nodes[i];
        // Find Y_A = C \ N[A} \ {A}
        // To find Y_A, mark all neighbors and A
        bool mark[MAXN];
        memset(mark, 0, sizeof(bool)*(n+1));
        for(int j=0; j<neighbor_size[A]; j++) mark[neighbors[A][j]] = true;
        mark[A] = true;
        // Count Y_A size and list
        int Y_size = 0;
        int Y_nodes[MAXN];
        for(int k=0; k<C_size; k++){
            int u = C_nodes[k];
            if(!mark[u]){
                Y_nodes[Y_size++] = u;
            }
        }
        if(Y_size ==0){
            // All edges are covered by A, so any B not connected to A and B != A
            answer += (long long)(C_size - neighbor_size[A] -1);
            continue;
        }
        // Increment countB for all neighbors of Y_A
        for(int y=0; y<Y_size; y++){
            int u = Y_nodes[y];
            for(int j=0; j<neighbor_size[u]; j++) countB[neighbors[u][j]]++;
        }
        // Now iterate over C to find B where countB[B] == Y_size
        for(int j=0; j<C_size; j++){
            int B = C_nodes[j];
            if(countB[B] == Y_size){
                // Check B not connected to A
                // Binary search in neighbors[A] for B
                bool connected_to_A = false;
                int left =0, right = neighbor_size[A]-1, mid;
                while(left <= right){
                    mid = (left + right)/2;
                    if(neighbors[A][mid] == B){
                        connected_to_A = true;
                        break;
                    }
                    else if(neighbors[A][mid] < B){
                        left = mid +1;
                    }
                    else{
                        right = mid -1;
                    }
                }
                if(connected_to_A) continue;
                // Check N[A] ∩ N[B} == empty
                bool overlap = false;
                for(int p=0; p<neighbor_size[A]; p++){
                    int neighbor = neighbors[A][p];
                    // Binary search in neighbors[B] for neighbor
                    int l =0, r = neighbor_size[B]-1, m;
                    while(l <= r){
                        m = (l + r)/2;
                        if(neighbors[B][m] == neighbor){
                            overlap = true;
                            break;
                        }
                        else if(neighbors[B][m] < neighbor){
                            l = m +1;
                        }
                        else{
                            r = m -1;
                        }
                    }
                    if(overlap) break;
                }
                if(!overlap){
                    answer++;
                }
            }
        }
        // Reset countB
        for(int y=0; y<Y_size; y++){
            int u = Y_nodes[y];
            for(int j=0; j<neighbor_size[u]; j++) countB[neighbors[u][j]]--;
        }
    }

    free(countB);
    // Print the answer
    printf("%lld\n", answer);
    // Free allocated memory
    for(int i=0;i<C_size;i++){
        int u = C_nodes[i];
        free(neighbors[u]);
        Edge* e = adj[u].head;
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    return 0;
}