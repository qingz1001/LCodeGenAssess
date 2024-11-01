#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_K 10005

typedef long long ll;

int N, K;
int P[MAX_N], C[MAX_N], M[MAX_N];
int T[MAX_K];
ll dp[MAX_N];
int children[MAX_N][2], child_cnt[MAX_N];

void add_child(int parent, int child) {
    children[parent][child_cnt[parent]++] = child;
}

ll min(ll a, ll b) {
    return a < b ? a : b;
}

void dfs(int node) {
    dp[node] = C[node];
    for (int i = 0; i < child_cnt[node]; i++) {
        int child = children[node][i];
        dfs(child);
        dp[node] += min(dp[child], (ll)M[child]);
    }
}

ll solve(ll time) {
    ll ans = 0;
    for (int i = 0; i < child_cnt[1]; i++) {
        int child = children[1][i];
        ans += min(dp[child], min((ll)M[child] * time, dp[child]));
    }
    return ans;
}

int main() {
    scanf("%d %d", &N, &K);
    
    for (int i = 2; i <= N; i++) {
        scanf("%d %d %d", &P[i], &C[i], &M[i]);
        add_child(P[i], i);
    }
    
    for (int i = 0; i < K; i++) {
        scanf("%d", &T[i]);
    }
    
    dfs(1);
    
    for (int i = 0; i < K; i++) {
        printf("%lld\n", solve(T[i]));
    }
    
    return 0;
}