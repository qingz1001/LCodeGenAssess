#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000001

int n;
int a[MAXN];
int vis[MAXN];
int in[MAXN];
int stack[MAXN], top;
int cnt[MAXN];

void dfs(int u) {
    vis[u] = 1;
    stack[top++] = u;
    if (!vis[a[u]]) {
        dfs(a[u]);
    } else if (!cnt[a[u]]) {
        while (stack[--top] != a[u]) {
            cnt[stack[top]] = 1;
        }
        cnt[a[u]] = 1;
    }
    top--;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        in[a[i]]++;
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i] && !in[i]) {
            dfs(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!cnt[i]) {
            ans++;
        }
    }

    printf("%d\n", ans);
    return 0;
}