#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXN * MAXN];
int head[MAXN];
int edge_count = 0;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int bfs(int start, int end, int n) {
    int queue[MAXN];
    int front = 0, rear = 0;
    int dist[MAXN];
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        for (int i = head[current]; i != -1; i = edges[i].next) {
            int next = edges[i].to;
            if (dist[next] == INT_MAX) {
                dist[next] = dist[current] + (i == head[current] ? 0 : 1);
                queue[rear++] = next;
            }
        }
    }

    return dist[end] == INT_MAX ? -1 : dist[end];
}

int main() {
    int N, A, B;
    scanf("%d %d %d", &N, &A, &B);

    for (int i = 1; i <= N; i++) {
        head[i] = -1;
    }

    for (int i = 1; i <= N; i++) {
        int K;
        scanf("%d", &K);
        for (int j = 0; j < K; j++) {
            int to;
            scanf("%d", &to);
            add_edge(i, to);
        }
    }

    int result = bfs(A, B, N);
    printf("%d\n", result);

    return 0;
}