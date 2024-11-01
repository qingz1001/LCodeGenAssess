#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000005
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef long long ll;

int n;
int parent[MAX_N];
ll a[MAX_N], b[MAX_N];
int children[MAX_N][2], child_cnt[MAX_N];

ll sum_a[MAX_N], sum_b[MAX_N];
int size[MAX_N], heavy[MAX_N];
ll dp[MAX_N];

void dfs1(int u) {
    sum_a[u] = a[u];
    sum_b[u] = b[u];
    size[u] = 1;
    
    for (int i = 0; i < child_cnt[u]; i++) {
        int v = children[u][i];
        dfs1(v);
        sum_a[u] += sum_a[v];
        sum_b[u] += sum_b[v];
        size[u] += size[v];
        if (heavy[u] == 0 || size[v] > size[heavy[u]]) {
            heavy[u] = v;
        }
    }
}

void dfs2(int u) {
    ll best = sum_a[u] * sum_b[1] - sum_b[u] * sum_a[1];
    int hv = heavy[u];
    
    if (hv) {
        dfs2(hv);
        if (sum_a[hv] * sum_b[u] > sum_b[hv] * sum_a[u]) {
            best = MIN(best, dp[hv]);
        }
    }
    
    for (int i = 0; i < child_cnt[u]; i++) {
        int v = children[u][i];
        if (v != hv) {
            dfs2(v);
            if (sum_a[v] * sum_b[u] > sum_b[v] * sum_a[u]) {
                best = MIN(best, dp[v]);
            }
        }
    }
    
    dp[u] = best;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 2; i <= n; i++) {
        scanf("%d", &parent[i]);
        children[parent[i]][child_cnt[parent[i]]++] = i;
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &b[i]);
    }
    
    dfs1(1);
    dfs2(1);
    
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll num = sum_a[1] * sum_b[i] - sum_b[1] * sum_a[i] + dp[i];
        ll den = sum_b[1] * sum_b[i];
        ans += ((num + den - 1) / den) * i;
    }
    
    printf("%lld\n", ans);
    
    return 0;
}