#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int k;
} Node;

typedef struct {
    Node *data;
    int size;
    int capacity;
} MinHeap;

void swap(Node *a, Node *b){
    Node temp = *a;
    *a = *b;
    *b = temp;
}

MinHeap* createMinHeap(int capacity){
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (Node*)malloc(sizeof(Node) * (capacity + 1));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void heapifyUp(MinHeap *heap, int idx){
    while(idx > 1){
        int parent = idx / 2;
        if(heap->data[parent].k > heap->data[idx].k){
            swap(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
        else{
            break;
        }
    }
}

void heapifyDown(MinHeap *heap, int idx){
    while(2 * idx <= heap->size){
        int smallest = idx;
        int left = 2 * idx;
        int right = 2 * idx + 1;
        if(left <= heap->size && heap->data[left].k < heap->data[smallest].k){
            smallest = left;
        }
        if(right <= heap->size && heap->data[right].k < heap->data[smallest].k){
            smallest = right;
        }
        if(smallest != idx){
            swap(&heap->data[smallest], &heap->data[idx]);
            idx = smallest;
        }
        else{
            break;
        }
    }
}

void pushHeap(MinHeap *heap, Node node){
    if(heap->size >= heap->capacity){
        return;
    }
    heap->size++;
    heap->data[heap->size] = node;
    heapifyUp(heap, heap->size);
}

Node popHeap(MinHeap *heap){
    Node top = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    heapifyDown(heap, 1);
    return top;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int *k = (int*)malloc((n + 1) * sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &k[i]);
    // Build adjacency list
    int **adj = (int**)malloc((n +1) * sizeof(int*));
    int *adj_size = (int*)malloc((n +1) * sizeof(int));
    for(int i=1;i<=n;i++) {
        adj[i] = (int*)malloc((n +1) * sizeof(int));
        adj_size[i] =0;
    }
    // In-degree for first topological sort
    int *in_degree1 = (int*)calloc(n +1, sizeof(int));
    // In-degree for second topological sort
    int *in_degree2 = (int*)calloc(n +1, sizeof(int));
    for(int i=0;i<m;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a][adj_size[a]++] = b;
        in_degree1[b]++;
        in_degree2[b]++;
    }
    // First Topological Sort with Min Heap based on k_i
    MinHeap *heap = createMinHeap(n);
    for(int i=1;i<=n;i++) {
        if(in_degree1[i] ==0){
            Node node;
            node.id = i;
            node.k = k[i];
            pushHeap(heap, node);
        }
    }
    int *sequence = (int*)malloc(n * sizeof(int));
    int idx =0;
    while(heap->size >0){
        Node current = popHeap(heap);
        sequence[idx++] = current.id;
        for(int i=0;i<adj_size[current.id];i++){
            int neighbor = adj[current.id][i];
            in_degree1[neighbor]--;
            if(in_degree1[neighbor]==0){
                Node node;
                node.id = neighbor;
                node.k = k[neighbor];
                pushHeap(heap, node);
            }
        }
    }
    // Output the sequence
    for(int i=0;i<n;i++){
        printf("%d%c", sequence[i], i==n-1? '\n':' ');
    }
    // Second Topological Sort for t_i
    // Use simple queue
    int *queue = (int*)malloc(n * sizeof(int));
    int front =0, rear =0;
    for(int i=1;i<=n;i++) {
        if(in_degree2[i]==0){
            queue[rear++] = i;
        }
    }
    int *topo_order = (int*)malloc(n * sizeof(int));
    idx =0;
    while(front < rear){
        int current = queue[front++];
        topo_order[idx++] = current;
        for(int i=0;i<adj_size[current];i++){
            int neighbor = adj[current][i];
            in_degree2[neighbor]--;
            if(in_degree2[neighbor]==0){
                queue[rear++] = neighbor;
            }
        }
    }
    // Compute t_i
    int *t = (int*)malloc((n +1) * sizeof(int));
    for(int i=1;i<=n;i++) t[i] =1;
    for(int i=0;i<n;i++){
        int current = topo_order[i];
        for(int j=0;j<adj_size[current];j++){
            int neighbor = adj[current][j];
            if(t[neighbor] < t[current] +1){
                t[neighbor] = t[current] +1;
            }
        }
    }
    // Output t_i
    for(int i=1;i<=n;i++){
        printf("%d%c", t[i], i==n? '\n':' ');
    }
    // Free memory
    free(k);
    for(int i=1;i<=n;i++) free(adj[i]);
    free(adj);
    free(adj_size);
    free(in_degree1);
    free(in_degree2);
    free(heap->data);
    free(heap);
    free(sequence);
    free(queue);
    free(topo_order);
    free(t);
    return 0;
}