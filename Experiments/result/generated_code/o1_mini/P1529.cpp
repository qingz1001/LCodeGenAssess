#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 52
#define INF 1000000000

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

typedef struct {
    int node;
    int dist;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
} MinHeap;

// Mapping function
int get_index(char c){
    if('A' <= c && c <= 'Z') return c - 'A';
    if('a' <= c && c <= 'z') return 26 + (c - 'a');
    return -1;
}

// Heap functions
MinHeap* create_heap(int max_size){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * (max_size +1));
    heap->size = 0;
    return heap;
}

void swap(HeapNode* a, HeapNode* b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heap_push(MinHeap* heap, int node, int dist){
    heap->size++;
    heap->data[heap->size].node = node;
    heap->data[heap->size].dist = dist;
    int i = heap->size;
    while(i >1 && heap->data[i].dist < heap->data[i/2].dist){
        swap(&heap->data[i], &heap->data[i/2]);
        i /=2;
    }
}

HeapNode heap_pop(MinHeap* heap){
    HeapNode top = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    int i=1, smallest=i;
    while(1){
        int left = 2*i, right = 2*i +1;
        if(left <= heap->size && heap->data[left].dist < heap->data[smallest].dist){
            smallest = left;
        }
        if(right <= heap->size && heap->data[right].dist < heap->data[smallest].dist){
            smallest = right;
        }
        if(smallest != i){
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int is_empty(MinHeap* heap){
    return heap->size ==0;
}

int main(){
    int P;
    scanf("%d", &P);
    Edge* adj[MAX_NODES];
    for(int i=0;i<MAX_NODES;i++) adj[i]=NULL;
    for(int i=0;i<P;i++){
        char u, v;
        int w;
        scanf(" %c %c %d", &u, &v, &w);
        int ui = get_index(u);
        int vi = get_index(v);
        Edge* e1 = (Edge*)malloc(sizeof(Edge));
        e1->to = vi;
        e1->weight = w;
        e1->next = adj[ui];
        adj[ui] = e1;
        Edge* e2 = (Edge*)malloc(sizeof(Edge));
        e2->to = ui;
        e2->weight = w;
        e2->next = adj[vi];
        adj[vi] = e2;
    }
    int dist[MAX_NODES];
    for(int i=0;i<MAX_NODES;i++) dist[i]=INF;
    int start = get_index('Z');
    dist[start]=0;
    MinHeap* heap = create_heap(MAX_NODES*10);
    heap_push(heap, start, 0);
    while(!is_empty(heap)){
        HeapNode current = heap_pop(heap);
        if(current.dist > dist[current.node]) continue;
        Edge* e = adj[current.node];
        while(e){
            if(dist[e->to] > dist[current.node] + e->weight){
                dist[e->to] = dist[current.node] + e->weight;
                heap_push(heap, e->to, dist[e->to]);
            }
            e = e->next;
        }
    }
    char res = 0;
    int min_dist = INF;
    for(int i=0;i<26;i++){
        if(dist[i] < min_dist){
            min_dist = dist[i];
            res = 'A' + i;
        }
    }
    printf("%c %d\n", res, min_dist);
    // Free memory
    for(int i=0;i<MAX_NODES;i++){
        Edge* e = adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(heap->data);
    free(heap);
    return 0;
}