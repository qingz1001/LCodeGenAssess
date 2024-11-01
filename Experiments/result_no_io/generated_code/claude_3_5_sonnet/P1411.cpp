#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 701
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef long long ll;

int n;
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], cnt;
ll dp[MAX_N][2], size[MAX_N];

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs(int u, int fa) {
    size[u] = 1;
    dp[u][0] = 1;
    dp[u][1] = 0;
    
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        
        dfs(v, u);
        size[u] += size[v];
        dp[u][0] *= (dp[v][0] + dp[v][1]);
        dp[u][1] = MAX(dp[u][1] * (dp[v][0] + dp[v][1]), dp[u][0] * dp[v][1]);
        dp[u][0] %= 1000000007;
        dp[u][1] %= 1000000007;
    }
    
    dp[u][1] = MAX(dp[u][1], size[u]);
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    
    dfs(1, 0);
    
    printf("%lld\n", MAX(dp[1][0], dp[1][1]));
    
    return 0;
}