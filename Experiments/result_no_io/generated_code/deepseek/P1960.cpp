#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5000
#define MAXM 100000

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXM];
int head[MAXN + 1], indegree[MAXN + 1], rank[MAXN + 1], queue[MAXN + 1];
int n, m, edge_count = 0;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
    indegree[v]++;
}

int topological_sort() {
    int front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int rank_count = 0;
    while (front < rear) {
        if (rear - front > 1) {
            return 1; // More than one way to rank
        }
        int u = queue[front++];
        rank[rank_count++] = u;
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            if (--indegree[v] == 0) {
                queue[rear++] = v;
            }
        }
    }

    return rank_count == n ? 0 : -1; // 0: unique rank, -1: no valid rank
}

int main() {
    memset(head, -1, sizeof(head));
    memset(indegree, 0, sizeof(indegree));

    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
    }

    int result = topological_sort();
    for (int i = 0; i < n; i++) {
        printf("%d\n", rank[i]);
    }
    printf("%d\n", result);

    return 0;
}