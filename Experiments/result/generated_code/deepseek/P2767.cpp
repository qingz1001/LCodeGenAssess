#include <stdio.h>
#include <string.h>

#define MOD 10007
#define MAXN 128

int dp[MAXN][MAXN];

int solve(int n, int m) {
    if (n == 0) return 1;
    if (dp[n][m] != -1) return dp[n][m];

    int count = 0;
    for (int i = 0; i <= n - 1; i++) {
        count = (count + solve(i, m) * solve(n - 1 - i, m)) % MOD;
    }

    dp[n][m] = count;
    return count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    memset(dp, -1, sizeof(dp));

    printf("%d\n", solve(n, m));

    return 0;
}