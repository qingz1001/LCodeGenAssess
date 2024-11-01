#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct Edge {
    int to, next;
    int color;
} Edge;

int n, cnt;
int head[MAXN], vis[MAXN];
long long ans, sum[MAXN][2];
Edge edge[MAXN * 2];

void addEdge(int u, int v, int c) {
    edge[cnt].to = v;
    edge[cnt].color = c;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u, int fa) {
    vis[u] = 1;
    long long white = 0, black = 0;
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        if (!vis[v]) {
            dfs(v, u);
            ans += sum[v][0] * (sum[v][1] + (edge[i].color == 1));
            ans += sum[v][1] * (sum[v][0] + (edge[i].color == 0));
            sum[u][0] += sum[v][0] + (edge[i].color == 0);
            sum[u][1] += sum[v][1] + (edge[i].color == 1);
        }
        if (edge[i].color == 0) white++;
        else black++;
    }
    ans += white * black;
}

int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        addEdge(u, v, c);
        addEdge(v, u, c);
    }
    dfs(1, 0);
    printf("%lld\n", ans);
    return 0;
}