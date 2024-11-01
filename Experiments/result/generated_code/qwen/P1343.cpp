#include <stdio.h>
#include <stdlib.h>

#define MAXN 205
#define INF 0x3f3f3f3f

typedef struct {
    int to, cap;
} Edge;

Edge edges[MAXN * MAXN];
int head[MAXN], edge_cnt = 0;

void add_edge(int from, int to, int cap) {
    edges[edge_cnt].to = to;
    edges[edge_cnt].cap = cap;
    edges[edge_cnt].next = head[from];
    head[from] = edge_cnt++;
}

int n, m, x;
int level[MAXN];
int cur[MAXN];

void bfs(int s) {
    for (int i = 1; i <= n; ++i) level[i] = -1;
    level[s] = 0;
    int front = 0, rear = 0;
    cur[s] = head[s];
    while (front != rear) {
        int u = edges[cur[front]].to;
        if (level[u] == -1 && edges[cur[front]].cap > 0) {
            level[u] = level[edges[cur[front]].from] + 1;
            cur[u] = head[u];
            rear++;
        }
        front++;
    }
}

int dfs(int u, int t, int f) {
    if (u == t) return f;
    int flow = 0;
    for (; cur[u] != -1; cur[u] = edges[cur[u]].next) {
        int v = edges[cur[u]].to;
        if (level[v] == level[u] + 1 && edges[cur[u]].cap > 0) {
            int d = dfs(v, t, f - flow);
            if (d > 0) {
                edges[cur[u]].cap -= d;
                edges[cur[u] ^ 1].cap += d;
                flow += d;
                if (flow == f) break;
            }
        }
    }
    return flow;
}

int max_flow(int s, int t) {
    int ans = 0;
    while (1) {
        bfs(s);
        if (level[t] == -1) break;
        for (int i = 1; i <= n; ++i) cur[i] = head[i];
        ans += dfs(s, t, INF);
    }
    return ans;
}

int main() {
    scanf("%d %d %d", &n, &m, &x);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        add_edge(a, b, c);
        add_edge(b, a, 0);
    }
    int maxFlow = max_flow(1, n);
    if (maxFlow < x) {
        printf("Orz Ni Jinan Saint Cow!\n");
    } else {
        printf("%d %d\n", x, (maxFlow + x - 1) / x);
    }
    return 0;
}