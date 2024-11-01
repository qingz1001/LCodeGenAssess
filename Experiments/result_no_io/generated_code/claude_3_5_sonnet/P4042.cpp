#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define MAX_M 1000005
#define INF 9223372036854775807LL

typedef long long ll;

int N, M;
ll S[MAX_N], K[MAX_N];
int R[MAX_N], cnt[MAX_N];
int head[MAX_N], to[MAX_M], nxt[MAX_M], tot;
ll dp[MAX_N];

void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs(int u) {
    if (dp[u] != INF) return;
    
    ll sum = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        dfs(v);
        sum += dp[v];
    }
    
    dp[u] = K[u];
    if (sum + S[u] < dp[u]) dp[u] = sum + S[u];
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld%lld%d", &S[i], &K[i], &R[i]);
        cnt[i] = R[i];
        for (int j = 1; j <= R[i]; j++) {
            int x;
            scanf("%d", &x);
            add_edge(i, x);
        }
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dfs(1);
    
    printf("%lld\n", dp[1]);
    
    return 0;
}