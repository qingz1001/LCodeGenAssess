#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXK 10005

typedef long long ll;

int N, K;
int P[MAXN], C[MAXN], M[MAXN];
int T[MAXK];
int child[MAXN], next[MAXN], head[MAXN], tot;
ll sum[MAXN], f[MAXN];

void addEdge(int u, int v) {
    child[++tot] = v;
    next[tot] = head[u];
    head[u] = tot;
}

void dfs(int u) {
    sum[u] = C[u];
    for (int i = head[u]; i; i = next[i]) {
        int v = child[i];
        dfs(v);
        sum[u] += sum[v];
        f[u] += f[v];
    }
    if (u != 1) {
        ll x = (sum[u] < M[u] ? sum[u] : M[u]);
        f[u] += x;
        sum[u] -= x;
    }
}

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 2; i <= N; i++) {
        scanf("%d%d%d", &P[i], &C[i], &M[i]);
        addEdge(P[i], i);
    }
    
    dfs(1);
    
    for (int i = 1; i <= K; i++) {
        scanf("%d", &T[i]);
        ll ans = f[1];
        ll remain = sum[1];
        for (int j = 2; j <= T[i] && remain; j++) {
            ll x = (remain < f[1] ? remain : f[1]);
            ans += x;
            remain -= x;
        }
        printf("%lld\n", ans);
    }
    
    return 0;
}