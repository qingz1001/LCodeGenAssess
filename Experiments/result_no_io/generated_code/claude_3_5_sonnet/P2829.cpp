#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 5001
#define MAX_M 100001

typedef struct Edge {
    int v, w;
    struct Edge* next;
} Edge;

typedef struct {
    int dist;
    int node;
} HeapNode;

Edge* graph[MAX_N];
int dist[MAX_N], dist2[MAX_N];
int n, m, k;
int degree[MAX_N];

void addEdge(int u, int v, int w) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->v = v;
    e->w = w;
    e->next = graph[u];
    graph[u] = e;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(HeapNode* heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].dist < heap[smallest].dist)
        smallest = left;
    if (right < size && heap[right].dist < heap[smallest].dist)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

void dijkstra() {
    HeapNode heap[MAX_N];
    int size = 0;

    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        dist2[i] = INT_MAX;
    }

    dist[1] = 0;
    heap[size++] = (HeapNode){0, 1};

    while (size > 0) {
        HeapNode node = heap[0];
        swap(&heap[0], &heap[--size]);
        minHeapify(heap, size, 0);

        int u = node.node;
        int d = node.dist;

        if (d > dist2[u]) continue;

        for (Edge* e = graph[u]; e; e = e->next) {
            int v = e->v;
            int w = e->w;

            if (degree[v] < k && v != 1 && v != n) continue;

            if (dist[v] > d + w) {
                dist2[v] = dist[v];
                dist[v] = d + w;
                heap[size++] = (HeapNode){dist[v], v};
                minHeapify(heap, size, size - 1);
            } else if (d + w < dist2[v] && d + w > dist[v]) {
                dist2[v] = d + w;
                heap[size++] = (HeapNode){dist2[v], v};
                minHeapify(heap, size, size - 1);
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
        degree[u]++;
        degree[v]++;
    }

    dijkstra();

    if (dist2[n] == INT_MAX)
        printf("-1\n");
    else
        printf("%d\n", dist2[n]);

    return 0;
}