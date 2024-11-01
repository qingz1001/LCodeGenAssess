#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_P 800
#define MAX_C 1450
#define INF 1000000000

typedef struct {
    int to;
    int weight;
} Edge;

typedef struct {
    int size;
    int nodes[MAX_P + 1];
    int dist[MAX_P + 1];
} Heap;

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify_up(Heap *heap, int index){
    while(index > 1){
        int parent = index / 2;
        if(heap->dist[heap->nodes[parent]] > heap->dist[heap->nodes[index]]){
            swap(&heap->nodes[parent], &heap->nodes[index]);
            index = parent;
        }
        else{
            break;
        }
    }
}

void heapify_down(Heap *heap, int index){
    while(2 * index <= heap->size){
        int smallest = index;
        int left = 2 * index;
        int right = 2 * index + 1;
        if(left <= heap->size && heap->dist[heap->nodes[left]] < heap->dist[heap->nodes[smallest]]){
            smallest = left;
        }
        if(right <= heap->size && heap->dist[heap->nodes[right]] < heap->dist[heap->nodes[smallest]]){
            smallest = right;
        }
        if(smallest != index){
            swap(&heap->nodes[smallest], &heap->nodes[index]);
            index = smallest;
        }
        else{
            break;
        }
    }
}

int extract_min(Heap *heap){
    if(heap->size == 0){
        return -1;
    }
    int min = heap->nodes[1];
    heap->nodes[1] = heap->nodes[heap->size];
    heap->size--;
    heapify_down(heap, 1);
    return min;
}

void insert_heap(Heap *heap, int node){
    heap->size++;
    heap->nodes[heap->size] = node;
    heapify_up(heap, heap->size);
}

int main(){
    int N, P, C;
    scanf("%d %d %d", &N, &P, &C);
    
    int cows_in_pasture[MAX_P + 1];
    for(int i = 1; i <= P; i++) cows_in_pasture[i] = 0;
    for(int i = 0; i < N; i++){
        int S;
        scanf("%d", &S);
        cows_in_pasture[S]++;
    }
    
    Edge adj[MAX_P + 1][MAX_C * 2];
    int adj_size[MAX_P + 1];
    for(int i = 1; i <= P; i++) adj_size[i] = 0;
    for(int i = 0; i < C; i++){
        int A, B, D;
        scanf("%d %d %d", &A, &B, &D);
        adj[A][adj_size[A]].to = B;
        adj[A][adj_size[A]++].weight = D;
        adj[B][adj_size[B]].to = A;
        adj[B][adj_size[B]++].weight = D;
    }
    
    long long sum_distance[MAX_P + 1];
    for(int i = 1; i <= P; i++) sum_distance[i] = 0;
    
    int dist[MAX_P + 1];
    for(int S = 1; S <= P; S++){
        if(cows_in_pasture[S] == 0) continue;
        for(int i = 1; i <= P; i++) dist[i] = INF;
        dist[S] = 0;
        
        Heap heap;
        heap.size = 0;
        insert_heap(&heap, S);
        
        while(heap.size > 0){
            int u = extract_min(&heap);
            for(int i = 0; i < adj_size[u]; i++){
                int v = adj[u][i].to;
                int w = adj[u][i].weight;
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    insert_heap(&heap, v);
                }
            }
        }
        
        for(int i = 1; i <= P; i++) sum_distance[i] += (long long)cows_in_pasture[S] * dist[i];
    }
    
    long long min_sum = INF * (long long)N;
    for(int i = 1; i <= P; i++) if(sum_distance[i] < min_sum) min_sum = sum_distance[i];
    
    printf("%lld\n", min_sum);
    return 0;
}