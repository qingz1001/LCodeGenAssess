#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20001
#define MAX_M 100001

struct Edge {
    int to, next, weight;
} edges[MAX_M * 2];

int head[MAX_N], cnt;
int color[MAX_N];
int n, m;

void add_edge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

int dfs(int u, int c, int mid) {
    color[u] = c;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (edges[i].weight > mid) continue;
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
    
    int max_weight = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
        if (w > max_weight) max_weight = w;
    }
    
    int left = 0, right = max_weight, ans = 0;
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