#include <stdio.h>
#include <stdlib.h>

#define MAXN 2005
#define MAXM 10005

int n, m;
int k[MAXN];
int u[MAXM], v[MAXM];
int in[MAXN], out[MAXN];
int ans[MAXN], min_pos[MAXN];
int stack[MAXN], top;
int visited[MAXN];

void dfs(int x) {
    visited[x] = 1;
    for (int i = in[x]; i < out[x]; i++) {
        if (!visited[u[i]]) {
            dfs(u[i]);
        }
    }
    stack[top++] = x;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &k[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u[i], &v[i]);
        in[v[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        out[i] = in[i] + out[i - 1];
        u[out[i]] = v[i];
    }
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    top = 0;
    for (int i = n; i >= 1; i--) {
        if (k[stack[i]] > top) {
            top = k[stack[i]];
        }
        ans[stack[i]] = ++top;
        min_pos[stack[i]] = ans[stack[i]];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (v[j] == i) {
                min_pos[u[j]] = (min_pos[u[j]] > ans[i] - 1) ? (ans[i] - 1) : min_pos[u[j]];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", min_pos[i]);
    }
    printf("\n");
    return 0;
}