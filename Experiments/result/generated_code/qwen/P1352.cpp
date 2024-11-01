#include <stdio.h>
#include <stdlib.h>

#define MAXN 6000

int n;
int r[MAXN];
int parent[MAXN];
int dp[MAXN][2];

void dfs(int node) {
    dp[node][0] = 0; // Not inviting the current node
    dp[node][1] = r[node]; // Inviting the current node

    for (int i = 1; i <= n; i++) {
        if (parent[i] == node) {
            dfs(i);
            dp[node][0] += dp[i][1]; // If not inviting the current node, invite all children
            dp[node][1] += fmax(dp[i][0], dp[i][1]); // If inviting the current node, choose the maximum of inviting or not inviting each child
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &r[i]);
    }

    for (int i = 1; i <= n; i++) {
        parent[i] = -1;
    }

    for (int i = 1; i < n; i++) {
        int l, k;
        scanf("%d %d", &l, &k);
        parent[l] = k;
    }

    dfs(1);

    printf("%d\n", fmax(dp[1][0], dp[1][1]));

    return 0;
}