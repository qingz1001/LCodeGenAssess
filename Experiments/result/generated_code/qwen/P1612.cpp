#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n;
int parent[MAXN];
int weight[MAXN];
int capacity[MAXN];
int dp[MAXN];

void dfs(int node) {
    dp[node] = 1;
    for (int i = 1; i <= n; i++) {
        if (parent[i] == node && weight[i] + weight[node] <= capacity[node]) {
            dfs(i);
            dp[node] = dp[i] + 1 > dp[node] ? dp[i] + 1 : dp[node];
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &parent[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &weight[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &capacity[i]);
    }

    dfs(1);

    for (int i = 1; i <= n; i++) {
        printf("%d ", dp[i]);
    }
    printf("\n");

    return 0;
}