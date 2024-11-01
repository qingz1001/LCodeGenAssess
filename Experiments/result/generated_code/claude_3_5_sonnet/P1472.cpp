#include <stdio.h>
#include <string.h>

#define MAXN 200
#define MAXK 100
#define MOD 9901

int dp[MAXN][MAXK];

int solve(int n, int k) {
    if (n % 2 == 0) return 0;
    if (k == 1) return (n == 1);
    if (n == 1) return 0;

    if (dp[n][k] != -1) return dp[n][k];

    int result = 0;
    for (int i = 1; i <= n - 2; i += 2) {
        result = (result + solve(i, k - 1) * solve(n - 1 - i, k - 1)) % MOD;
    }

    dp[n][k] = result;
    return result;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    memset(dp, -1, sizeof(dp));

    int answer = solve(n, k);
    printf("%d\n", answer);

    return 0;
}