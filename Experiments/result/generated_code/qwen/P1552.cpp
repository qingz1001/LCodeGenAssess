#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int boss;
    int salary;
    long long leadership;
} Ninja;

int n, m;
Ninja ninjas[MAXN];
long long dp[MAXN][2];

void dfs(int u) {
    dp[u][0] = 0;
    dp[u][1] = ninjas[u].salary * ninjas[u].leadership;
    for (int v = 0; v < n; ++v) {
        if (ninjas[v].boss == u) {
            dfs(v);
            dp[u][0] += dp[v][0];
            dp[u][1] += dp[v][0];
            dp[u][1] = fmax(dp[u][1], dp[u][0] + dp[v][1]);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %lld", &ninjas[i].boss, &ninjas[i].salary, &ninjas[i].leadership);
    }

    for (int i = 0; i < n; ++i) {
        dp[i][0] = -1;
        dp[i][1] = -1;
    }

    dfs(0);

    long long max_satisfaction = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[i][1] <= m) {
            max_satisfaction = fmax(max_satisfaction, dp[i][1]);
        }
    }

    printf("%lld\n", max_satisfaction);

    return 0;
}