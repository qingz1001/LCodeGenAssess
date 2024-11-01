#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 200005
#define MAX_M 1000005

typedef struct Edge {
    int to, weight;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
int dist[MAX_N];
int visited[MAX_N];

typedef struct {
    int node;
    int distance;
} HeapNode;

HeapNode heap[MAX_M];
int heap_size = 0;

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(int node, int distance) {
    heap_size++;
    int current = heap_size;
    heap[current].node = node;
    heap[current].distance = distance;

    while (current > 1 && heap[current / 2].distance > heap[current].distance) {
        swap(&heap[current], &heap[current / 2]);
        current /= 2;
    }
}

HeapNode pop() {
    HeapNode result = heap[1];
    heap[1] = heap[heap_size];
    heap_size--;

    int current = 1;
    while (current * 2 <= heap_size) {
        int child = current * 2;
        if (child + 1 <= heap_size && heap[child + 1].distance < heap[child].distance) {
            child++;
        }
        if (heap[current].distance <= heap[child].distance) {
            break;
        }
        swap(&heap[current], &heap[child]);
        current = child;
    }

    return result;
}

void add_edge(int from, int to, int weight) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = to;
    edge->weight = weight;
    edge->next = graph[from];
    graph[from] = edge;
}

int dijkstra(int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[1] = 0;
    push(1, 0);

    while (heap_size > 0) {
        HeapNode node = pop();
        int u = node.node;

        if (visited[u]) continue;
        visited[u] = 1;

        if (u == n) return dist[n];

        for (Edge* edge = graph[u]; edge != NULL; edge = edge->next) {
            int v = edge->to;
            int weight = edge->weight;

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

    memset(graph, 0, sizeof(graph));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, 0);
    }

    int result = dijkstra(n);
    printf("%d\n", result);

    return 0;
}