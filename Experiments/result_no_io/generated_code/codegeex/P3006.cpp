#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct node {
    ll c, m, sum;
    struct node *next;
} node;

node *adj[100005];
ll size[100005];
ll cow[100005];
ll dp[100005];
ll sum[100005];
ll cnt[100005];
ll ans[10005];
ll n, k;

void addEdge(int u, int v, ll c, ll m) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->c = c;
    newNode->m = m;
    newNode->sum = m;
    newNode->next = adj[u];
    adj[u] = newNode;
}

void dfs(int u) {
    if (u != 1) {
        node *v = adj[u];
        dfs(v->c);
        sum[u] = sum[v->c] + v->sum;
        cow[u] = cow[v->c] + v->c->c;
    }
}

void dfs2(int u) {
    if (u != 1) {
        node *v = adj[u];
        if (dp[v->c] > 0) {
            ll t = (dp[v->c] - cow[v->c] - 1) / v->m + 1;
            v->sum = v->m * t;
            cnt[u] = cnt[v->c] + t;
        } else {
            v->sum = 0;
            cnt[u] = cnt[v->c];
        }
        dfs2(v->c);
        dp[u] = sum[u] + cnt[u];
    }
}

int main() {
    scanf("%lld %lld", &n, &k);
    for (int i = 1; i <= n; i++) {
        ll x, c, m;
        scanf("%lld %lld %lld", &x, &c, &m);
        addEdge(i, x, c, m);
    }
    dfs(1);
    dp[1] = cow[1];
    dfs2(1);
    for (int i = 1; i <= k; i++) {
        ll t;
        scanf("%lld", &t);
        ans[i] = dp[1] + (t - cnt[1] - 1) / size[1] + 1;
    }
    for (int i = 1; i <= k; i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}