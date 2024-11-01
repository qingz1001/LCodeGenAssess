#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXK 105

int A[MAXN];
int dp[MAXK][MAXN];

int main() {
    int n, k, L, R;
    scanf("%d %d %d %d", &n, &k, &L, &R);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &A[i]);
    }

    for (int i = 1; i <= n; ++i) {
        dp[1][i] = dp[1][i - 1] + A[i];
    }

    for (int j = 2; j <= k; ++j) {
        for (int i = j * L; i <= j * R && i <= n; ++i) {
            dp[j][i] = dp[j][i - 1];
            for (int l = i - L; l < i; ++l) {
                dp[j][i] = fmax(dp[j][i], dp[j - 1][l] + dp[1][i] - dp[1][l]);
            }
        }
    }

    printf("%d\n", dp[k][n]);

    return 0;
}