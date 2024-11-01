#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

int n, a[MAXN], vis[MAXN], match[MAXN], ans;

int dfs(int u) {
    for (int v = 1; v <= n; v++) {
        if (!vis[v] && a[v] == u) {
            vis[v] = 1;
            if (!match[v] || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= n; i++) {
        ans += dfs(i);
    }

    printf("%d\n", ans);
    return 0;
}