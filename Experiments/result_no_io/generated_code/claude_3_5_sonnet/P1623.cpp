#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MOD 1000000000

int n;
int tree[MAX_N][MAX_N];
int size[MAX_N];
int dp[MAX_N][2];
long long ways[MAX_N][2];

void dfs(int node, int parent) {
    dp[node][0] = 0;
    dp[node][1] = 0;
    ways[node][0] = 1;
    ways[node][1] = 1;

    for (int i = 0; i < size[node]; i++) {
        int child = tree[node][i];
        if (child != parent) {
            dfs(child, node);
            
            long long temp = ways[node][0];
            ways[node][0] = (ways[node][0] * ways[child][0]) % MOD;
            ways[node][1] = (ways[node][1] * ways[child][0]) % MOD;
            
            if (dp[node][0] < dp[node][1] + dp[child][0]) {
                dp[node][0] = dp[node][1] + dp[child][0];
                ways[node][0] = ways[node][1] * ways[child][0] % MOD;
            } else if (dp[node][0] == dp[node][1] + dp[child][0]) {
                ways[node][0] = (ways[node][0] + ways[node][1] * ways[child][0] % MOD) % MOD;
            }
            
            if (dp[node][1] < dp[child][0] + 1) {
                dp[node][1] = dp[child][0] + 1;
                ways[node][1] = temp * ways[child][0] % MOD;
            } else if (dp[node][1] == dp[child][0] + 1) {
                ways[node][1] = (ways[node][1] + temp * ways[child][0] % MOD) % MOD;
            }
        }
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int node, m;
        scanf("%d %d", &node, &m);
        size[node] = m;
        for (int j = 0; j < m; j++) {
            scanf("%d", &tree[node][j]);
        }
    }

    dfs(1, 0);

    int max_matching = (dp[1][0] > dp[1][1]) ? dp[1][0] : dp[1][1];
    long long total_ways = (dp[1][0] > dp[1][1]) ? ways[1][0] : 
                           ((dp[1][0] < dp[1][1]) ? ways[1][1] : (ways[1][0] + ways[1][1]) % MOD);

    printf("%d\n%lld\n", max_matching, total_ways);

    return 0;
}