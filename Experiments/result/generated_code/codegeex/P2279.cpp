#include <stdio.h>
#include <stdbool.h>

#define MAXN 1005

int n, a[MAXN], ans;
bool vis[MAXN];

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = true;
    dfs(a[u]);
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
            ans++;
        }
    }

    printf("%d\n", ans);
    return 0;
}