#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20001
#define MAXK 500001

typedef long long ll;

int n, k;
int parent[MAXN], a[MAXN], v[MAXN];
int child[MAXN][MAXN], child_count[MAXN];
int depth[MAXN];
ll dp[MAXN][MAXK];

void dfs(int node, int d) {
    depth[node] = d;
    for (int i = 0; i < child_count[node]; i++) {
        dfs(child[node][i], d + 1);
    }
}

ll max(ll a, ll b) {
    return a > b ? a : b;
}

void solve() {
    scanf("%d %d", &n, &k);
    memset(child_count, 0, sizeof(child_count));
    
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &parent[i], &a[i], &v[i]);
        if (i > 1) {
            child[parent[i]][child_count[parent[i]]++] = i;
        }
    }
    
    dfs(1, 1);
    
    memset(dp, 0, sizeof(dp));
    
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j <= k; j++) {
            if (i == 1 || j > 0) {
                for (int t = 0; t <= a[i] && t <= j; t++) {
                    ll val = (ll)t * v[i];
                    if (i > 1) {
                        val += dp[parent[i]][j - t];
                    }
                    for (int c = 0; c < child_count[i]; c++) {
                        int child_node = child[i][c];
                        val += dp[child_node][k + depth[child_node] - depth[i]];
                    }
                    dp[i][j] = max(dp[i][j], val);
                }
            }
        }
    }
    
    printf("%lld\n", dp[1][k]);
}

int main() {
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        solve();
    }
    return 0;
}