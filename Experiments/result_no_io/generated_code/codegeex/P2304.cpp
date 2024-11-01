#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 100005
#define INF 0x3f3f3f3f

int n, m, ans, x[MAXN], y[MAXN], p[MAXN], q[MAXN], f[MAXN], g[MAXN], h[MAXN];
int dp[MAXN], pre[MAXN], nxt[MAXN], vis[MAXN], stack[MAXN];

inline int cmp(const void *a, const void *b) {
    return ((int *)a)[0] - ((int *)b)[0];
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &y[i]);
        x[i] = abs(x[i]);
        y[i] = abs(y[i]);
        p[i] = x[i] + y[i];
        q[i] = x[i] - y[i];
        f[i] = g[i] = h[i] = i;
    }

    qsort(f + 1, n, sizeof(int), cmp);
    qsort(g + 1, n, sizeof(int), cmp);
    qsort(h + 1, n, sizeof(int), cmp);

    for (int i = 1; i <= n; i++) {
        while (p[f[i]] > p[f[i + 1]]) f[i] = f[i + 1];
        while (q[g[i]] > q[g[i + 1]]) g[i] = g[i + 1];
        while (p[h[i]] < p[h[i + 1]]) h[i] = h[i + 1];
    }

    int top = 0;
    for (int i = 1; i <= n; i++) {
        while (top && x[f[stack[top]]] > x[f[i]]) top--;
        pre[f[i]] = stack[top];
        stack[++top] = f[i];
    }

    top = 0;
    for (int i = 1; i <= n; i++) {
        while (top && x[g[stack[top]]] > x[g[i]]) top--;
        pre[g[i]] = stack[top];
        stack[++top] = g[i];
    }

    top = 0;
    for (int i = 1; i <= n; i++) {
        while (top && x[h[stack[top]]] < x[h[i]]) top--;
        nxt[h[i]] = stack[top];
        stack[++top] = h[i];
    }

    memset(dp, INF, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (pre[f[i]] != 0) dp[i] = min(dp[i], dp[pre[f[i]]] + 1);
        if (pre[g[i]] != 0) dp[i] = min(dp[i], dp[pre[g[i]]] + 1);
        if (nxt[h[i]] != 0) dp[i] = min(dp[i], dp[nxt[h[i]]] + 1);
    }

    ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] != INF) {
            ans = i;
            vis[i] = 1;
        }
    }

    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) {
        if (vis[i]) printf("%d ", i);
    }
    printf("\n");

    memset(dp, INF, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (pre[f[i]] != 0) dp[f[i]] = min(dp[f[i]], dp[pre[f[i]]]);
        if (pre[g[i]] != 0) dp[g[i]] = min(dp[g[i]], dp[pre[g[i]]]);
        if (nxt[h[i]] != 0) dp[h[i]] = min(dp[h[i]], dp[nxt[h[i]]]);
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] != INF) cnt++;
    }

    printf("%d\n", cnt);
    return 0;
}