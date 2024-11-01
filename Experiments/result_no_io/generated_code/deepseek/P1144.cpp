#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MOD 100003
#define MAXN 1000005
#define MAXM 2000005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
int dist[MAXN], ways[MAXN];
bool visited[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void bfs(int start) {
    memset(dist, -1, sizeof(dist));
    memset(ways, 0, sizeof(ways));
    memset(visited, false, sizeof(visited));

    dist[start] = 0;
    ways[start] = 1;
    visited[start] = true;

    int queue[MAXN], front = 0, rear = 0;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            if (dist[v] == -1 || dist[v] == dist[u] + 1) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    queue[rear++] = v;
                }
                ways[v] = (ways[v] + ways[u]) % MOD;
            }
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    memset(head, -1, sizeof(head));

    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }

    bfs(1);

    for (int i = 1; i <= N; i++) {
        printf("%d\n", ways[i]);
    }

    return 0;
}