#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int n, s;
int a[MAXN], b[MAXN], t[MAXN];
int dist[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) dist[i] = -1;
    dist[start] = 0;
    int *heap = (int *)malloc(n * sizeof(int));
    int heap_size = 0;
    int *heap_pos = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) heap_pos[i] = -1;

    void push(int v) {
        heap[heap_size++] = v;
        while (heap_size > 1 && dist[heap[(heap_size >> 1)] + 1] < dist[v]) {
            heap_pos[heap[(heap_size >> 1)] + 1] = heap_size;
            heap[(heap_size >> 1)] = heap[--heap_size];
            heap_pos[heap[(heap_size >> 1)] + 1] = heap_size >> 1;
        }
        heap_pos[v + 1] = heap_size;
    }

    void pop() {
        heap[1] = heap[--heap_size];
        heap_pos[heap[1] + 1] = 1;
        while ((heap_size & 1) == 0 && dist[heap[(heap_size >> 1)] + 1] < dist[heap[(heap_size >> 1) ^ 1]]) {
            heap_pos[heap[(heap_size >> 1)] + 1] = heap_size;
            heap[(heap_size >> 1)] = heap[(heap_size >> 1) ^ 1];
            heap_pos[heap[(heap_size >> 1)] + 1] = heap_size >> 1;
        }
        heap_pos[heap[1] + 1] = 1;
    }

    void update(int v, int d) {
        if (d >= dist[v + 1]) return;
        dist[v + 1] = d;
        push(v);
    }

    for (int i = 1; i <= n; i++) push(i);

    while (heap_size > 0) {
        int u = heap[1];
        pop();
        for (int j = 1; j <= n; j++) {
            if (dist[j + 1] == -1 || dist[u + 1] + t[j] < dist[j + 1]) {
                update(j, dist[u + 1] + t[j]);
            }
        }
    }

    free(heap);
    free(heap_pos);
}

int main() {
    scanf("%d", &n);
    scanf("%d", &s);
    for (int i = 1; i < n; i++) {
        scanf("%d %d %d", &a[i], &b[i], &t[i]);
    }
    dijkstra(s);
    int max_dist = -1;
    for (int i = 1; i <= n; i++) {
        if (dist[i] != -1 && dist[i] > max_dist) {
            max_dist = dist[i];
        }
    }
    printf("%d\n", max_dist / 2);
    return 0;
}