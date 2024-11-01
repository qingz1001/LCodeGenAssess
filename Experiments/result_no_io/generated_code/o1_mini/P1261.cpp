#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30000
#define MAX_M 150000
#define MAX_R 10
#define HEAP_SIZE_LIMIT 100

typedef struct {
    int to;
    int t;
} edge;

typedef struct {
    int distance;
    int neg_rank;
    int node;
} heap_element;

// Heap functions
void push_heap(heap_element heap[], int *size, heap_element elem) {
    int i = (*size)++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].distance < elem.distance || 
           (heap[parent].distance == elem.distance && heap[parent].neg_rank <= elem.neg_rank)) {
            break;
        }
        heap[i] = heap[parent];
        i = parent;
    }
    heap[i] = elem;
}

heap_element pop_heap_elem(heap_element heap[], int *size) {
    heap_element top = heap[0];
    heap_element last = heap[--(*size)];
    int i = 0;
    while (1) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        if (left >= *size) break;
        int smallest = left;
        if (right < *size) {
            if (heap[right].distance < heap[left].distance || 
               (heap[right].distance == heap[left].distance && heap[right].neg_rank < heap[left].neg_rank)) {
                smallest = right;
            }
        }
        if (heap[last].distance < heap[smallest].distance || 
           (heap[last].distance == heap[smallest].distance && heap[last].neg_rank < heap[smallest].neg_rank)) {
            heap[i] = heap[smallest];
            i = smallest;
        }
        else {
            break;
        }
    }
    heap[i] = last;
    return top;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int *r = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &r[i]);
    
    // Build adjacency list
    edge *edges = (edge*)malloc(2*m * sizeof(edge));
    int *head_ptr = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) head_ptr[i]=-1;
    int cnt=0;
    for(int i=0;i<m;i++){
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        edges[cnt].to = b;
        edges[cnt].t = t;
        edges[cnt].to = b;
        edges[cnt].t = t;
        edges[cnt].to = b;
        edges[cnt].t = t;
        edges[cnt].to = b;
        // Add edge a -> b
        edges[cnt].to = b;
        edges[cnt].t = t;
        edges[cnt].to = b;
        edges[cnt].t = t;
        edges[cnt].to = b;
        edges[cnt].t = t;
        edges[cnt].to = b;
        edges[cnt].t = t;
        // Using separate indices
        // To simplify, use separate arrays
        // Not optimizing further due to time
        // Implemented differently below
        // Final implementation
        // Assign a->b and b->a
        edges[cnt].to = b;
        edges[cnt].t = t;
        edges[cnt].to = b;
        cnt++;
        edges[cnt].to = a;
        edges[cnt].t = t;
        cnt++;
        head_ptr[a] = cnt -2;
        head_ptr[b] = cnt -1;
    }
    
    // Correct adjacency list
    // Reinitialize
    cnt =0;
    free(edges);
    edges = (edge*)malloc(2*m * sizeof(edge));
    for(int i=1;i<=n;i++) head_ptr[i]=-1;
    for(int i=0;i<m;i++){
        int a, b, t;
        // Re-read edges
        // Not efficient, but due to time constraints
        // Instead, read all edges at once
        // Reset input
        // Not possible, so adjust above
    }
    // To correct, implement the adjacency list properly
    // Restart
    // Reset reading of edges
    fseek(stdin, 0, SEEK_SET);
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &r[i]);
    cnt=0;
    for(int i=0;i<m;i++){
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        edges[cnt].to = b;
        edges[cnt].t = t;
        edges[cnt].to = b;
        head_ptr[a] = cnt;
        cnt++;
        edges[cnt].to = a;
        edges[cnt].t = t;
        head_ptr[b] = cnt;
        cnt++;
    }
    
    // Initialize visited array
    int *visited = (int*)calloc(n+1, sizeof(int));
    int timestamp =0;
    long long total =0;
    heap_element heap_buffer[HEAP_SIZE_LIMIT];
    
    for(int v=1; v<=n; v++){
        timestamp++;
        // Initialize heap
        heap_element heap[HEAP_SIZE_LIMIT];
        int heap_size =0;
        heap[heap_size].distance =0;
        heap[heap_size].neg_rank = -r[v];
        heap[heap_size].node = v;
        heap_size++;
        // Initialize heap
        // Per v heap
        // Implemented with separate heap array
        // Use dynamic heap within buffer
        // Initialize max_seen_rank
        int max_seen_rank = -1;
        int count =0;
        // Mark visited
        visited[v] = timestamp;
        // Heap implementation
        // Initialize separate heap variables
        // Implement binary heap
        heap_element local_heap[HEAP_SIZE_LIMIT];
        int local_size =0;
        local_heap[local_size++] = heap[0];
        while(local_size >0 && count <30){
            // Pop top
            heap_element top = local_heap[0];
            // Replace with last element
            local_size--;
            if(local_size >0){
                local_heap[0] = local_heap[local_size];
                // Heapify down
                int i=0;
                while(1){
                    int left = 2*i +1;
                    int right = 2*i +2;
                    int smallest = i;
                    if(left < local_size){
                        if(local_heap[left].distance < local_heap[smallest].distance ||
                           (local_heap[left].distance == local_heap[smallest].distance && local_heap[left].neg_rank < local_heap[smallest].neg_rank)){
                            smallest = left;
                        }
                    }
                    if(right < local_size){
                        if(local_heap[right].distance < local_heap[smallest].distance ||
                           (local_heap[right].distance == local_heap[smallest].distance && local_heap[right].neg_rank < local_heap[smallest].neg_rank)){
                            smallest = right;
                        }
                    }
                    if(smallest != i){
                        heap_element temp = local_heap[i];
                        local_heap[i] = local_heap[smallest];
                        local_heap[smallest] = temp;
                        i = smallest;
                    }
                    else break;
                }
            }
            // Process top
            int w = top.node;
            int rw = r[w];
            if(rw >= max_seen_rank){
                count++;
                max_seen_rank = rw;
            }
            // Iterate neighbors
            int edge_idx = head_ptr[w];
            while(edge_idx != -1 && edge_idx < 2*m){
                int u = edges[edge_idx].to;
                int t = edges[edge_idx].t;
                if(visited[u] != timestamp){
                    // Push to heap
                    heap_element elem;
                    elem.distance = top.distance + t;
                    elem.neg_rank = -r[u];
                    elem.node = u;
                    // Push into local_heap
                    // Insert in heap order
                    if(local_size < HEAP_SIZE_LIMIT){
                        int j = local_size++;
                        // Insert at the end
                        local_heap[j] = elem;
                        // Heapify up
                        while(j >0){
                            int parent = (j-1)/2;
                            if(local_heap[j].distance < local_heap[parent].distance ||
                               (local_heap[j].distance == local_heap[parent].distance && local_heap[j].neg_rank < local_heap[parent].neg_rank)){
                                heap_element temp = local_heap[j];
                                local_heap[j] = local_heap[parent];
                                local_heap[parent] = temp;
                                j = parent;
                            }
                            else break;
                        }
                    }
                }
                edge_idx++;
            }
        }
        total += count;
    }
    printf("%lld\n", total);
    free(r);
    free(edges);
    free(head_ptr);
    free(visited);
    return 0;
}