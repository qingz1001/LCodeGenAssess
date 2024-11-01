#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 200005

int N, M;
int head[MAX_N], nxt[MAX_M], to[MAX_M], cnt;
int dp[MAX_N];

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs(int u) {
    if (dp[u]) return;
    dp[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        dfs(v);
        if (dp[v] + 1 > dp[u]) {
            dp[u] = dp[v] + 1;
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add_edge(x, y);
    }
    
    for (int i = 1; i <= N; i++) {
        dfs(i);
    }
    
    for (int i = 1; i <= N; i++) {
        printf("%d\n", dp[i]);
    }
    
    return 0;
}