#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 1000005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], vis[MAXN], d[MAXN], in_degree[MAXN], out_degree[MAXN];
int n, m, edge_count;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void dfs(int u, int depth) {
    vis[u] = 1;
    d[u] = depth;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!vis[v]) {
            dfs(v, depth + 1);
        } else {
            int cycle_length = abs(d[u] - d[v] + 1);
            if (cycle_length > 0) {
                int g = gcd(cycle_length, depth - d[v] + 1);
                if (g > 1) {
                    d[u] = d[v] + 1;
                }
            }
        }
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        out_degree[a]++;
        in_degree[b]++;
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, 0);
        }
    }

    int max_k = 0, min_k = 3;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] > 0 || out_degree[i] > 0) {
            max_k = gcd(max_k, d[i]);
        }
    }

    if (max_k < 3) {
        printf("-1 -1\n");
    } else {
        printf("%d %d\n", max_k, min_k);
    }

    return 0;
}