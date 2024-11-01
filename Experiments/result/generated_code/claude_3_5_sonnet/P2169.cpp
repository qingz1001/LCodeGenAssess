#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 200001
#define MAX_M 1000001

typedef struct Edge {
    int to, weight;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
int dist[MAX_N];
int visited[MAX_N];

typedef struct {
    int node;
    int dist;
} HeapNode;

HeapNode heap[MAX_M];
int heap_size = 0;

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(int node, int distance) {
    heap[heap_size].node = node;
    heap[heap_size].dist = distance;
    int current = heap_size;
    heap_size++;

    while (current > 0) {
        int parent = (current - 1) / 2;
        if (heap[parent].dist <= heap[current].dist) break;
        swap(&heap[parent], &heap[current]);
        current = parent;
    }
}

HeapNode pop() {
    HeapNode min = heap[0];
    heap_size--;
    heap[0] = heap[heap_size];

    int current = 0;
    while (1) {
        int left_child = 2 * current + 1;
        int right_child = 2 * current + 2;
        int smallest = current;

        if (left_child < heap_size && heap[left_child].dist < heap[smallest].dist)
            smallest = left_child;
        if (right_child < heap_size && heap[right_child].dist < heap[smallest].dist)
            smallest = right_child;

        if (smallest == current) break;

        swap(&heap[current], &heap[smallest]);
        current = smallest;
    }

    return min;
}

void add_edge(int from, int to, int weight) {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->to = to;
    new_edge->weight = weight;
    new_edge->next = graph[from];
    graph[from] = new_edge;
}

int dijkstra(int start, int end, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[start] = 0;
    push(start, 0);

    while (heap_size > 0) {
        HeapNode node = pop();
        int u = node.node;

        if (visited[u]) continue;
        visited[u] = 1;

        if (u == end) return dist[u];

        for (Edge* e = graph[u]; e != NULL; e = e->next) {
            int v = e->to;
            int weight = e->weight;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                push(v, dist[v]);
            }
        }
    }

    return -1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, 0);  // 双向连接，反向权重为0
    }

    int result = dijkstra(1, n, n);
    printf("%d\n", result);

    return 0;
}