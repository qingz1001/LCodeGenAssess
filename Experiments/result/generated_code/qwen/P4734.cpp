#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int n;
int v[MAXN];
int dp[2][MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }

    dp[0][1] = v[1];
    dp[1][1] = 0;

    for (int i = 2; i <= n; i++) {
        dp[0][i] = max(dp[0][i-1], dp[1][i-1] + v[i]);
        dp[1][i] = max(dp[1][i-1], dp[0][i-1]);
    }

    printf("%d\n", max(dp[0][n], dp[1][n]));

    return 0;
}