#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAXN 10005
#define MAXM 50005

typedef struct {
    int to, next, cost;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
int n, m, b;
int fee[MAXN];
bool visited[MAXN];
int max_fee[MAXN];

void add_edge(int u, int v, int c) {
    edges[edge_count].to = v;
    edges[edge_count].cost = c;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

bool dfs(int u, int max_fee_allowed) {
    if (u == n) return true;
    visited[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        int cost = edges[i].cost;
        if (!visited[v] && fee[v] <= max_fee_allowed && max_fee[u] + cost <= b) {
            max_fee[v] = max_fee[u] + cost;
            if (dfs(v, max_fee_allowed)) return true;
        }
    }
    return false;
}

int main() {
    scanf("%d %d %d", &n, &m, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &fee[i]);
        head[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        add_edge(a, b, c);
        add_edge(b, a, c);
    }

    int low = fee[1], high = INT_MAX;
    int result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        for (int i = 1; i <= n; i++) {
            visited[i] = false;
            max_fee[i] = 0;
        }
        if (fee[1] <= mid && dfs(1, mid)) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (result == -1) {
        printf("AFK\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}