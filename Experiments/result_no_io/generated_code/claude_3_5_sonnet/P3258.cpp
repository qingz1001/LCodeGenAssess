#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 300005

int n;
int a[MAX_N];
int candy[MAX_N];
int visited[MAX_N];
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], tot;

void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs(int u, int prev) {
    visited[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v != prev) {
            dfs(v, u);
            candy[u] += candy[v];
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    
    for (int i = n - 1; i >= 1; i--) {
        if (a[i] != a[i+1]) {
            candy[a[i]]++;
            candy[a[i+1]]++;
        }
    }
    
    dfs(1, 0);
    
    for (int i = 1; i <= n; i++) {
        printf("%d\n", candy[i]);
    }
    
    return 0;
}