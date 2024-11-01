#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int n;
int a[MAX_N * 2 + 1];
long long dp[MAX_N * 2 + 1][MAX_N * 2 + 1];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i + n] = a[i];
    }

    memset(dp, 0, sizeof(dp));

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= 2 * n - len + 1; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                dp[i][j] = MAX(dp[i][j], dp[i][k] + dp[k + 1][j] + (long long)a[i] * a[k + 1] * a[j + 1]);
            }
        }
    }

    long long max_energy = 0;
    for (int i = 1; i <= n; i++) {
        max_energy = MAX(max_energy, dp[i][i + n - 1]);
    }

    printf("%lld\n", max_energy);

    return 0;
}