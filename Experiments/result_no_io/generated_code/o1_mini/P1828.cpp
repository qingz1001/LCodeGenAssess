#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_P 800
#define MAX_C 1450
#define INF 1000000000

typedef struct {
    int to;
    int weight;
    int next;
} Edge;

typedef struct {
    int node;
    int dist;
} HeapNode;

Edge edges[2 * MAX_C];
int head_list[MAX_P + 1];
int edge_cnt = 0;

void add_edge(int u, int v, int w){
    edges[edge_cnt].to = v;
    edges[edge_cnt].weight = w;
    edges[edge_cnt].next = head_list[u];
    head_list[u] = edge_cnt++;
}

typedef struct {
    HeapNode data[800 * 10];
    int size;
} MinHeap;

void heap_init(MinHeap *heap){
    heap->size = 0;
}

void heap_push(MinHeap *heap, int node, int dist){
    int i = heap->size++;
    heap->data[i].node = node;
    heap->data[i].dist = dist;
    while(i > 0){
        int parent = (i - 1) / 2;
        if(heap->data[parent].dist <= heap->data[i].dist) break;
        HeapNode temp = heap->data[parent];
        heap->data[parent] = heap->data[i];
        heap->data[i] = temp;
        i = parent;
    }
}

HeapNode heap_pop(MinHeap *heap){
    HeapNode top = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int i = 0;
    while(1){
        int left = 2*i + 1, right = 2*i + 2, smallest = i;
        if(left < heap->size && heap->data[left].dist < heap->data[smallest].dist) smallest = left;
        if(right < heap->size && heap->data[right].dist < heap->data[smallest].dist) smallest = right;
        if(smallest == i) break;
        HeapNode temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;
        i = smallest;
    }
    return top;
}

int main(){
    int N, P, C;
    scanf("%d %d %d", &N, &P, &C);
    int count[MAX_P + 1];
    memset(count, 0, sizeof(count));
    for(int i = 0; i < N; i++){
        int p;
        scanf("%d", &p);
        count[p]++;
    }
    memset(head_list, -1, sizeof(head_list));
    for(int i = 0; i < C; i++){
        int A, B, D;
        scanf("%d %d %d", &A, &B, &D);
        add_edge(A, B, D);
        add_edge(B, A, D);
    }
    long long sum_dist[MAX_P + 1];
    for(int i = 1; i <= P; i++) sum_dist[i] = 0;
    int distance_arr[MAX_P + 1];
    int visited[MAX_P + 1];
    MinHeap heap;
    heap_init(&heap);
    for(int s = 1; s <= P; s++) if(count[s] > 0){
        for(int i = 1; i <= P; i++) distance_arr[i] = INF;
        memset(visited, 0, sizeof(visited));
        distance_arr[s] = 0;
        heap_init(&heap);
        heap_push(&heap, s, 0);
        while(heap.size > 0){
            HeapNode current = heap_pop(&heap);
            int u = current.node;
            if(visited[u]) continue;
            visited[u] = 1;
            sum_dist[u] += (long long)current.dist * count[s];
            for(int e = head_list[u]; e != -1; e = edges[e].next){
                int v = edges[e].to;
                int w = edges[e].weight;
                if(!visited[v] && distance_arr[v] > distance_arr[u] + w){
                    distance_arr[v] = distance_arr[u] + w;
                    heap_push(&heap, v, distance_arr[v]);
                }
            }
        }
    }
    long long min_sum = INF;
    for(int i = 1; i <= P; i++) if(sum_dist[i] < min_sum) min_sum = sum_dist[i];
    printf("%lld\n", min_sum);
    return 0;
}