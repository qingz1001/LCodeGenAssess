#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 1000000005

typedef long long ll;

int N, M;
int B[MAX_N], C[MAX_N], L[MAX_N];
int child[MAX_N][2], child_cnt[MAX_N];
ll dp[MAX_N][2];

void add_child(int parent, int child) {
    if (child_cnt[parent] < 2) {
        child[parent][child_cnt[parent]++] = child;
    }
}

ll max(ll a, ll b) {
    return a > b ? a : b;
}

void dfs(int node) {
    dp[node][0] = 0;
    dp[node][1] = C[node];

    for (int i = 0; i < child_cnt[node]; i++) {
        int c = child[node][i];
        dfs(c);

        for (int j = M; j >= 0; j--) {
            if (dp[node][1] != -1 && j >= C[node]) {
                dp[node][1] = max(dp[node][1], dp[c][0] + C[node]);
                if (j >= dp[c][1])
                    dp[node][1] = max(dp[node][1], dp[c][1]);
            }
            if (dp[node][0] != -1) {
                if (dp[c][0] != -1)
                    dp[node][0] = max(dp[node][0], dp[c][0]);
                if (j >= dp[c][1] && dp[c][1] != -1)
                    dp[node][0] = max(dp[node][0], dp[c][1]);
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        scanf("%d %d %d", &B[i], &C[i], &L[i]);
        add_child(B[i], i);
    }

    memset(dp, -1, sizeof(dp));
    dfs(0);

    ll ans = 0;
    for (int i = 0; i <= N; i++) {
        if (dp[i][0] != -1)
            ans = max(ans, dp[i][0] * L[i]);
        if (dp[i][1] != -1)
            ans = max(ans, dp[i][1] * L[i]);
    }

    printf("%lld\n", ans);

    return 0;
}