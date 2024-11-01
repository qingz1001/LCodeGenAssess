#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 50005
#define MAXM 50005
#define MAXK 20005
#define INF INT_MAX

typedef struct {
    int to, next, cost, dict_node;
} Edge;

typedef struct {
    int v, w;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size, capacity;
} MinHeap;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
int dist[MAXN], visited[MAXN];
int n, m, k;

void add_edge(int u, int v, int cost, int dict_node) {
    edges[edge_count].to = v;
    edges[edge_count].cost = cost;
    edges[edge_count].dict_node = dict_node;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap *heap, int idx) {
    while (idx > 1 && heap->data[idx].w < heap->data[idx / 2].w) {
        swap(&heap->data[idx], &heap->data[idx / 2]);
        idx /= 2;
    }
}

void heapify_down(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx;
    int right = 2 * idx + 1;

    if (left <= heap->size && heap->data[left].w < heap->data[smallest].w) {
        smallest = left;
    }
    if (right <= heap->size && heap->data[right].w < heap->data[smallest].w) {
        smallest = right;
    }
    if (smallest != idx) {
        swap(&heap->data[idx], &heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

void push(MinHeap *heap, int v, int w) {
    if (heap->size == heap->capacity) return;
    heap->size++;
    heap->data[heap->size].v = v;
    heap->data[heap->size].w = w;
    heapify_up(heap, heap->size);
}

HeapNode pop(MinHeap *heap) {
    HeapNode result = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    heapify_down(heap, 1);
    return result;
}

int dijkstra(int start) {
    MinHeap heap;
    heap.data = (HeapNode *)malloc((MAXN + 1) * sizeof(HeapNode));
    heap.capacity = MAXN;
    heap.size = 0;

    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[start] = 0;
    push(&heap, start, 0);

    while (heap.size > 0) {
        HeapNode node = pop(&heap);
        int u = node.v;
        if (visited[u]) continue;
        visited[u] = 1;

        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            int cost = edges[i].cost;
            int dict_node = edges[i].dict_node;
            int lcp_cost = strlen(dict_node); // Simplified LCP calculation

            if (dist[u] + cost + lcp_cost < dist[v]) {
                dist[v] = dist[u] + cost + lcp_cost;
                push(&heap, v, dist[v]);
            }
        }
    }

    free(heap.data);
    return dist[n];
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &m, &k);
        memset(head, -1, sizeof(head));
        edge_count = 0;

        for (int i = 0; i < m; i++) {
            int a, b, c, d;
            scanf("%d %d %d %d", &a, &b, &c, &d);
            add_edge(a, b, c, d);
        }

        for (int i = 0; i < k - 1; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            // Store dictionary tree edges if needed
        }

        for (int i = 2; i <= n; i++) {
            printf("%d\n", dijkstra(i));
        }
    }
    return 0;
}