#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define MOD 1000000007

typedef struct Node {
    int id;
    int m;
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

    for (int i = 0; i < tree[u].m; i++) {
        int v = tree[u].children[i];
        dfs(v);

        dp[u][0] += dp[v][1];
        cnt[u][0] = (cnt[u][0] * cnt[v][1]) % MOD;

        if (dp[v][0] > dp[v][1]) {
            dp[u][1] += dp[v][0];
            cnt[u][1] = (cnt[u][1] * cnt[v][0]) % MOD;
        } else if (dp[v][0] < dp[v][1]) {
            dp[u][1] += dp[v][1];
            cnt[u][1] = (cnt[u][1] * cnt[v][1]) % MOD;
        } else {
            dp[u][1] += dp[v][0];
            cnt[u][1] = (cnt[u][1] * (cnt[v][0] + cnt[v][1])) % MOD;
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
        tree[id].m = m;
        for (int j = 0; j < m; j++) {
            scanf("%d", &tree[id].children[j]);
        }
    }

    dfs(1);

    if (dp[1][0] > dp[1][1]) {
        printf("%d\n%lld\n", dp[1][0], cnt[1][0]);
    } else if (dp[1][0] < dp[1][1]) {
        printf("%d\n%lld\n", dp[1][1], cnt[1][1]);
    } else {
        printf("%d\n%lld\n", dp[1][0], (cnt[1][0] + cnt[1][1]) % MOD);
    }

    return 0;
}