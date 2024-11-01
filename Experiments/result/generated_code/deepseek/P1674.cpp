#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200
#define MAXP 40000

typedef struct {
    int to, len;
} Edge;

typedef struct {
    Edge edges[MAXP];
    int size;
} Graph;

Graph graph[MAXN + 1];
int dist[MAXN + 1];
int visited[MAXN + 1];

void add_edge(int u, int v, int len) {
    graph[u].edges[graph[u].size].to = v;
    graph[u].edges[graph[u].size].len = len;
    graph[u].size++;
}

int dfs(int u, int max_len, int t) {
    if (u == t) return 1;
    visited[u] = 1;
    for (int i = 0; i < graph[u].size; i++) {
        int v = graph[u].edges[i].to;
        int len = graph[u].edges[i].len;
        if (!visited[v] && len <= max_len) {
            if (dfs(v, max_len, t)) {
                visited[u] = 0;
                return 1;
            }
        }
    }
    visited[u] = 0;
    return 0;
}

int can_find_t_paths(int max_len, int t, int n) {
    int count = 0;
    for (int i = 0; i < t; i++) {
        if (dfs(1, max_len, n)) {
            count++;
        } else {
            break;
        }
    }
    return count >= t;
}

int main() {
    int N, P, T;
    scanf("%d %d %d", &N, &P, &T);

    for (int i = 0; i < P; i++) {
        int A, B, L;
        scanf("%d %d %d", &A, &B, &L);
        add_edge(A, B, L);
        add_edge(B, A, L);
    }

    int left = 0, right = 1000000;
    while (left < right) {
        int mid = (left + right) / 2;
        if (can_find_t_paths(mid, T, N)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);
    return 0;
}