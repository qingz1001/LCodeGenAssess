#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005

typedef struct Node {
    int id;
    int num_children;
    int children[MAXN];
} Node;

Node tree[MAXN];
int dp[MAXN][2]; // dp[i][0]表示不选i的最大匹配数，dp[i][1]表示选i的最大匹配数
long long cnt[MAXN][2]; // cnt[i][0]表示不选i的最大匹配方案数，cnt[i][1]表示选i的最大匹配方案数

void dfs(int u) {
    dp[u][0] = 0;
    dp[u][1] = 1;
    cnt[u][0] = 1;
    cnt[u][1] = 1;

    for (int i = 0; i < tree[u].num_children; i++) {
        int v = tree[u].children[i];
        dfs(v);

        dp[u][0] += dp[v][1];
        cnt[u][0] = (cnt[u][0] * cnt[v][1]) % 1000000007;

        if (dp[v][0] > dp[v][1]) {
            dp[u][1] += dp[v][0];
            cnt[u][1] = (cnt[u][1] * cnt[v][0]) % 1000000007;
        } else if (dp[v][0] < dp[v][1]) {
            dp[u][1] += dp[v][1];
            cnt[u][1] = (cnt[u][1] * cnt[v][1]) % 1000000007;
        } else {
            dp[u][1] += dp[v][0];
            cnt[u][1] = (cnt[u][1] * (cnt[v][0] + cnt[v][1])) % 1000000007;
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
        int id, m;
        scanf("%d %d", &id, &m);
        tree[id].id = id;
        tree[id].num_children = m;
        for (int j = 0; j < m; j++) {
            scanf("%d", &tree[id].children[j]);
        }
    }

    dfs(1);

    int max_match = dp[1][0];
    long long max_match_count = cnt[1][0];

    if (dp[1][1] > dp[1][0]) {
        max_match = dp[1][1];
        max_match_count = cnt[1][1];
    } else if (dp[1][1] == dp[1][0]) {
        max_match_count = (cnt[1][0] + cnt[1][1]) % 1000000007;
    }

    printf("%d\n", max_match);
    printf("%lld\n", max_match_count);

    return 0;
}