#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001
#define MAXM 200001

typedef struct {
    int v;
    struct Edge *next;
} Edge;

Edge *head[MAXN];
int dist[MAXN];

void addEdge(int u, int v) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->v = v;
    e->next = head[u];
    head[u] = e;
}

void bfs(int start) {
    int visited[MAXN] = {0};
    visited[start] = 1;
    dist[start] = 1;
    Edge *e;
    int queue[MAXN], front = 0, rear = 0;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];
        for (e = head[u]; e; e = e->next) {
            int v = e->v;
            if (!visited[v]) {
                visited[v] = 1;
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        addEdge(y, x); // Reverse the direction since we need to find the furthest city to the east
    }

    for (int i = 1; i <= N; i++) {
        bfs(i);
    }

    for (int i = 1; i <= N; i++) {
        printf("%d\n", dist[i]);
    }

    return 0;
}