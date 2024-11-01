#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000
#define MAXK 1000
#define MAX_QUEUE 1000
#define MAX_HEAP (MAXN)

typedef struct {
    int node;
    int sum;
} HeapNode;

typedef struct {
    HeapNode data[MAX_HEAP];
    int size;
} MaxHeap;

void heap_init(MaxHeap *heap) {
    heap->size = 0;
}

void heap_push(MaxHeap *heap, HeapNode val) {
    int i = heap->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent].sum >= val.sum) break;
        heap->data[i] = heap->data[parent];
        i = parent;
    }
    heap->data[i] = val;
}

HeapNode heap_pop(MaxHeap *heap) {
    HeapNode top = heap->data[0];
    HeapNode last = heap->data[--heap->size];
    int i = 0;
    while (i * 2 + 1 < heap->size) {
        int left = i * 2 + 1;
        int right = i * 2 + 2;
        int best = left;
        if (right < heap->size && heap->data[right].sum > heap->data[left].sum)
            best = right;
        if (heap->data[best].sum <= last.sum)
            break;
        heap->data[i] = heap->data[best];
        i = best;
    }
    heap->data[i] = last;
    return top;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, k, r;
        scanf("%d %d %d", &n, &k, &r);
        int w[MAXN];
        for(int i=0;i<n;i++) scanf("%d", &w[i]);
        // Build adjacency list
        int adj[MAXN][MAXN];
        int adj_size[MAXN];
        for(int i=0;i<n;i++) adj_size[i]=0;
        for(int i=0;i<n-1;i++){
            int x, y;
            scanf("%d %d", &x, &y);
            x--, y--;
            adj[x][adj_size[x]++] = y;
            adj[y][adj_size[y]++] = x;
        }
        // Precompute coverage
        int cover_nodes[MAXN][MAXN];
        int cover_size[MAXN];
        for(int u=0; u<n; u++){
            cover_size[u]=0;
            // BFS from u
            int queue[MAXN];
            int front=0, back=0;
            int visited[MAXN];
            memset(visited, 0, sizeof(int)*n);
            queue[back++] = u;
            visited[u]=1;
            int dist =0;
            while(front < back && dist <= r){
                int level_size = back - front;
                for(int i=0;i<level_size;i++){
                    int current = queue[front++];
                    cover_nodes[u][cover_size[u]++] = current;
                    for(int j=0; j<adj_size[current]; j++){
                        int neighbor = adj[current][j];
                        if(!visited[neighbor]){
                            visited[neighbor]=1;
                            queue[back++] = neighbor;
                        }
                    }
                }
                dist++;
            }
        }
        // Initialize heap
        MaxHeap heap;
        heap_init(&heap);
        int sum_cover[MAXN];
        for(int u=0; u<n; u++){
            int s =0;
            for(int i=0;i<cover_size[u];i++) s += w[cover_nodes[u][i]];
            sum_cover[u] = s;
            HeapNode hn = {u, s};
            heap_push(&heap, hn);
        }
        // Initialize covered
        int covered[MAXN];
        memset(covered, 0, sizeof(int)*n);
        long long total =0;
        for(int i=0;i<k;i++){
            while(heap.size >0){
                HeapNode top = heap_pop(&heap);
                int u = top.node;
                int current_sum =0;
                for(int j=0; j<cover_size[u]; j++) if(!covered[cover_nodes[u][j]]) current_sum += w[cover_nodes[u][j]];
                if(current_sum == top.sum){
                    total += current_sum;
                    for(int j=0; j<cover_size[u]; j++) covered[cover_nodes[u][j]] =1;
                    break;
                }
                else{
                    if(current_sum >0){
                        HeapNode new_hn = {u, current_sum};
                        heap_push(&heap, new_hn);
                    }
                }
            }
        }
        printf("%lld\n", total);
    }
}