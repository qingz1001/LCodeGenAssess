#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 5000
#define MAXM 100000

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXM];
int head[MAXN + 1], indegree[MAXN + 1], rank[MAXN + 1];
int n, m, edge_count;

void add_edge(int from, int to) {
    edges[edge_count].to = to;
    edges[edge_count].next = head[from];
    head[from] = edge_count++;
    indegree[to]++;
}

bool topological_sort() {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int rank_count = 0;
    while (front < rear) {
        if (rear - front > 1) {
            return true; // More than one way to sort
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

    return false; // Only one way to sort
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        indegree[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
    }

    bool multiple_ways = topological_sort();

    for (int i = 0; i < n; i++) {
        printf("%d\n", rank[i]);
    }
    printf("%d\n", multiple_ways ? 1 : 0);

    return 0;
}