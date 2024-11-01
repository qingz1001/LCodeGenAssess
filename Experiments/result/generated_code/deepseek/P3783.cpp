#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 50005
#define MAXM 50005
#define MAXK 20005
#define INF INT_MAX

typedef struct {
    int to, time, dict_node;
} Edge;

typedef struct {
    int node, dist;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
} MinHeap;

Edge edges[MAXM];
int head[MAXN], next_edge[MAXM], edge_count;
int dist[MAXN];
int dict_tree[MAXK][26], dict_depth[MAXK], dict_count;

void add_edge(int from, int to, int time, int dict_node) {
    edges[edge_count] = (Edge){to, time, dict_node};
    next_edge[edge_count] = head[from];
    head[from] = edge_count++;
}

void init_dict_tree() {
    memset(dict_tree, -1, sizeof(dict_tree));
    dict_count = 1;
}

void add_dict_node(int parent, int ch) {
    dict_tree[parent][ch] = dict_count++;
    dict_depth[dict_count - 1] = dict_depth[parent] + 1;
}

void dijkstra(int start, int n) {
    MinHeap heap;
    heap.data = (HeapNode *)malloc((n + 1) * sizeof(HeapNode));
    heap.size = 0;

    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[start] = 0;
    heap.data[heap.size++] = (HeapNode){start, 0};

    while (heap.size > 0) {
        HeapNode min_node = heap.data[0];
        int min_index = 0;
        for (int i = 1; i < heap.size; i++) {
            if (heap.data[i].dist < min_node.dist) {
                min_node = heap.data[i];
                min_index = i;
            }
        }
        heap.data[min_index] = heap.data[--heap.size];

        int u = min_node.node;
        for (int i = head[u]; i != -1; i = next_edge[i]) {
            Edge e = edges[i];
            int v = e.to;
            int new_dist = dist[u] + e.time + dict_depth[e.dict_node];
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                heap.data[heap.size++] = (HeapNode){v, new_dist};
            }
        }
    }

    free(heap.data);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);

        memset(head, -1, sizeof(head));
        edge_count = 0;

        for (int i = 0; i < m; i++) {
            int a, b, c, d;
            scanf("%d %d %d %d", &a, &b, &c, &d);
            add_edge(a, b, c, d);
        }

        init_dict_tree();
        for (int i = 1; i < k; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            add_dict_node(u, w);
        }

        dijkstra(1, n);

        for (int i = 2; i <= n; i++) {
            printf("%d\n", dist[i]);
        }
    }
    return 0;
}