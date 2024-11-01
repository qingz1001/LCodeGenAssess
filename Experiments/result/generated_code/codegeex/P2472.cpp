#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 21
#define MAXE 100001

int n, m, d, s, t, cnt = 1;
int h[MAXN][MAXN], dep[MAXN*MAXN], head[MAXN*MAXN];
struct Edge {
    int to, next, flow, cost;
} edge[MAXE];

void add_edge(int u, int v, int f, int c) {
    edge[++cnt].to = v;
    edge[cnt].flow = f;
    edge[cnt].cost = c;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void add(int u, int v, int f, int c) {
    add_edge(u, v, f, c);
    add_edge(v, u, 0, -c);
}

int bfs() {
    memset(dep, 0, sizeof(dep));
    dep[s] = 1;
    int q[MAXN*MAXN], front = 0, rear = 0;
    q[rear++] = s;
    while (front < rear) {
        int u = q[front++];
        for (int i = head[u]; i; i = edge[i].next) {
            int v = edge[i].to;
            if (!dep[v] && edge[i].flow) {
                dep[v] = dep[u] + 1;
                q[rear++] = v;
            }
        }
    }
    return dep[t];
}

int dfs(int u, int a) {
    if (u == t || !a) return a;
    int flow = 0, f;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (dep[v] == dep[u] + 1 && (f = dfs(v, a - flow))) {
            flow += f;
            edge[i].flow -= f;
            edge[i^1].flow += f;
            if (flow == a) break;
        }
    }
    return flow;
}

int main() {
    scanf("%d%d%d", &n, &m, &d);
    s = 0, t = n * m + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%1d", &h[i][j]);
            if (h[i][j]) add(s, (i-1) * m + j, h[i][j], 0);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            scanf(" %c", &c);
            if (c == 'L') {
                add((i-1) * m + j, t, 1, 0);
                for (int x = i-d; x <= i+d; x++) {
                    for (int y = j-d; y <= j+d; y++) {
                        if (x < 1 || x > n || y < 1 || y > m || (x == i && y == j)) continue;
                        if (h[x][y] >= 2) add((i-1) * m + j, (x-1) * m + y, 1, 1);
                    }
                }
            }
        }
    }
    int ans = 0;
    while (bfs()) {
        ans += dfs(s, 0x3f3f3f3f);
    }
    printf("%d\n", ans);
    return 0;
}