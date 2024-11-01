#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define INF 1000000000

typedef struct {
    int parent, cost, leadership;
} Ninja;

Ninja ninjas[MAXN];
int n, m;

typedef struct {
    int size;
    int cost_sum;
    int *heap;
} MinHeap;

MinHeap *create_heap(int max_size) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->cost_sum = 0;
    heap->heap = (int *)malloc(max_size * sizeof(int));
    return heap;
}

void heapify_up(MinHeap *heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (ninjas[heap->heap[idx]].cost < ninjas[heap->heap[parent]].cost) {
            int temp = heap->heap[idx];
            heap->heap[idx] = heap->heap[parent];
            heap->heap[parent] = temp;
            idx = parent;
        } else {
            break;
        }
    }
}

void heapify_down(MinHeap *heap, int idx) {
    while (2 * idx + 1 < heap->size) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;
        if (left < heap->size && ninjas[heap->heap[left]].cost < ninjas[heap->heap[smallest]].cost) {
            smallest = left;
        }
        if (right < heap->size && ninjas[heap->heap[right]].cost < ninjas[heap->heap[smallest]].cost) {
            smallest = right;
        }
        if (smallest != idx) {
            int temp = heap->heap[idx];
            heap->heap[idx] = heap->heap[smallest];
            heap->heap[smallest] = temp;
            idx = smallest;
        } else {
            break;
        }
    }
}

void insert(MinHeap *heap, int ninja_idx) {
    heap->heap[heap->size] = ninja_idx;
    heap->cost_sum += ninjas[ninja_idx].cost;
    heap->size++;
    heapify_up(heap, heap->size - 1);
}

int extract_min(MinHeap *heap) {
    int min_idx = heap->heap[0];
    heap->cost_sum -= ninjas[min_idx].cost;
    heap->heap[0] = heap->heap[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return min_idx;
}

MinHeap *merge_heaps(MinHeap *a, MinHeap *b) {
    if (a->size < b->size) {
        MinHeap *temp = a;
        a = b;
        b = temp;
    }
    for (int i = 0; i < b->size; i++) {
        insert(a, b->heap[i]);
    }
    free(b->heap);
    free(b);
    return a;
}

MinHeap *dfs(int node) {
    MinHeap *heap = create_heap(MAXN);
    insert(heap, node);
    for (int i = 0; i < n; i++) {
        if (ninjas[i].parent == node) {
            MinHeap *child_heap = dfs(i);
            heap = merge_heaps(heap, child_heap);
        }
    }
    while (heap->cost_sum > m) {
        extract_min(heap);
    }
    return heap;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &ninjas[i].parent, &ninjas[i].cost, &ninjas[i].leadership);
    }

    int max_satisfaction = 0;
    for (int i = 0; i < n; i++) {
        if (ninjas[i].parent == 0) {
            MinHeap *heap = dfs(i);
            int satisfaction = heap->size * ninjas[i].leadership;
            if (satisfaction > max_satisfaction) {
                max_satisfaction = satisfaction;
            }
            free(heap->heap);
            free(heap);
        }
    }

    printf("%d\n", max_satisfaction);
    return 0;
}