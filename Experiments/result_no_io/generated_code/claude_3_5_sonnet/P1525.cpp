#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20001
#define MAXM 100001

struct Edge {
    int to, next, w;
} edge[MAXM * 2];

int head[MAXN], cnt;
int color[MAXN];
int n, m;

void addEdge(int u, int v, int w) {
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

int dfs(int u, int c, int mid) {
    color[u] = c;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (edge[i].w <= mid) continue;
        if (color[v] == c) return 0;
        if (color[v] == 0 && !dfs(v, 3 - c, mid)) return 0;
    }
    return 1;
}

int check(int mid) {
    memset(color, 0, sizeof(color));
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0 && !dfs(i, 1, mid)) return 0;
    }
    return 1;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    
    int left = 0, right = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
        if (w > right) right = w;
    }
    
    int ans = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    printf("%d\n", ans);
    return 0;
}