#include <stdio.h>
#include <stdlib.h>

#define MAXN 6005

int n;
int r[MAXN];
int parent[MAXN];
int dp[MAXN][2];

void dfs(int u) {
    dp[u][0] = 0; // Not attending u
    dp[u][1] = r[u]; // Attending u

    for (int i = 0; i < n; i++) {
        if (parent[i] == u) {
            dfs(i);
            dp[u][0] += dp[i][1]; // If u is not attended, all subordinates can be attended
            dp[u][1] += dp[i][0]; // If u is attended, subordinates cannot be attended
        }
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &r[i]);
        parent[i] = -1;
    }

    int m = n - 1;
    while (m--) {
        int l, k;
        scanf("%d %d", &l, &k);
        parent[l - 1] = k - 1;
    }

    dfs(0); // Assuming the root is always 0

    printf("%d\n", dp[0][1]); // Output the maximum happiness index

    return 0;
}