#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 500005

int n;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], tot;
int ans[MAXN], cnt;
bool vis[MAXN];

void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

bool dfs(int u, int fa, int dep) {
    vis[u] = true;
    ans[++cnt] = u;
    
    if (u == n && cnt == n) return true;
    
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        
        if (!vis[v] && dep < 2 && dfs(v, u, dep + 1)) return true;
    }
    
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        
        if (!vis[v] && dfs(v, u, 1)) return true;
    }
    
    vis[u] = false;
    cnt--;
    return false;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    
    if (dfs(1, 0, 0)) {
        for (int i = 1; i <= n; i++) {
            printf("%d\n", ans[i]);
        }
    } else {
        printf("BRAK\n");
    }
    
    return 0;
}