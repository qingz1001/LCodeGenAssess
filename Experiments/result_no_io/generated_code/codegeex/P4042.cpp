#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

typedef struct {
    ll k, s;
    int to[1000010], next[1000010], last, e;
} Graph;

Graph g[200010];
ll dp[200010];
int n, que[200010], head, tail;

void addedge(int u, int v) {
    g[u].e++;
    g[u].to[g[u].e] = v;
    g[u].next[g[u].e] = g[u].last;
    g[u].last = g[u].e;
}

void spfa() {
    for (int i = 1; i <= n; i++) dp[i] = LLONG_MAX;
    dp[1] = 0;
    que[tail++] = 1;
    while (head < tail) {
        int u = que[head++];
        for (int i = g[u].last; i; i = g[u].next[i]) {
            int v = g[u].to[i];
            if (dp[v] > dp[u] + g[u].s) {
                dp[v] = dp[u] + g[u].s;
                if (head == tail) que[tail++] = v;
                else if (dp[que[head]] > dp[que[tail - 1]]) que[--head] = v;
                else que[tail++] = v;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int r;
        scanf("%lld%lld%d", &g[i].s, &g[i].k, &r);
        for (int j = 1; j <= r; j++) {
            int v;
            scanf("%d", &v);
            addedge(i, v);
        }
    }
    spfa();
    ll ans = LLONG_MAX;
    for (int i = 1; i <= n; i++) ans = (ans < dp[i] + g[i].k) ? ans : dp[i] + g[i].k;
    printf("%lld\n", ans);
    return 0;
}