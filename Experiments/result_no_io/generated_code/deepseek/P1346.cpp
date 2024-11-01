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
int switch_count[MAXN];
int visited[MAXN];
int edge_count = 0;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void bfs(int start, int end, int n) {
    for (int i = 1; i <= n; i++) {
        switch_count[i] = INT_MAX;
        visited[i] = 0;
    }
    switch_count[start] = 0;
    int queue[MAXN];
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            if (!visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
                if (i == head[u]) {
                    switch_count[v] = switch_count[u];
                } else {
                    switch_count[v] = switch_count[u] + 1;
                }
            } else if (i != head[u]) {
                switch_count[v] = min(switch_count[v], switch_count[u] + 1);
            }
        }
    }
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
            int v;
            scanf("%d", &v);
            add_edge(i, v);
        }
    }

    bfs(A, B, N);

    if (switch_count[B] == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", switch_count[B]);
    }

    return 0;
}