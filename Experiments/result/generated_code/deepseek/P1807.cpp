#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1500
#define MAXM 50000

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], indegree[MAXN], dp[MAXN];
int n, m, edge_count;

void add_edge(int u, int v, int w) {
    edges[edge_count].v = v;
    edges[edge_count].w = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
    indegree[v]++;
}

void topological_sort() {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v;
            int w = edges[i].w;
            if (dp[u] != INT_MIN && dp[u] + w > dp[v]) {
                dp[v] = dp[u] + w;
            }
            if (--indegree[v] == 0) {
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        dp[i] = INT_MIN;
    }
    dp[1] = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    topological_sort();

    if (dp[n] == INT_MIN) {
        printf("-1\n");
    } else {
        printf("%d\n", dp[n]);
    }

    return 0;
}