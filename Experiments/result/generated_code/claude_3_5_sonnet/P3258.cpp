#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300005

int n;
int a[MAXN];
int head[MAXN], to[MAXN * 2], next[MAXN * 2], cnt;
int vis[MAXN], candy[MAXN];

void addEdge(int u, int v) {
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
}

void dfs(int u, int fa) {
    vis[u]++;
    for (int i = head[u]; i; i = next[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        candy[u] += candy[v];
    }
    if (candy[u] == 0 && u != a[n - 1]) candy[u] = 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
    }
    
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;
        addEdge(x, y);
        addEdge(y, x);
    }
    
    for (int i = 0; i < n - 1; i++) {
        int u = a[i], v = a[i + 1];
        while (u != v) {
            if (vis[u] < vis[v]) {
                candy[u]++;
                vis[u]++;
                for (int j = head[u]; j; j = next[j]) {
                    if (to[j] != a[i - 1]) {
                        u = to[j];
                        break;
                    }
                }
            } else {
                candy[v]++;
                vis[v]++;
                for (int j = head[v]; j; j = next[j]) {
                    if (to[j] != a[i + 2]) {
                        v = to[j];
                        break;
                    }
                }
            }
        }
    }
    
    dfs(0, -1);
    
    for (int i = 0; i < n; i++) {
        printf("%d\n", candy[i]);
    }
    
    return 0;
}