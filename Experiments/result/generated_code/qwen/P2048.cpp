#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int A[MAXN];
int dp[MAXN][MAXN];

int main() {
    int n, k, L, R;
    scanf("%d %d %d %d", &n, &k, &L, &R);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &A[i]);
    }

    for (int len = L; len <= R; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            dp[i][j] = dp[i + 1][j - 1] + A[j] - A[i];
        }
    }

    int max_beauty = -2e9;
    for (int i = 1; i + k - 1 <= n; ++i) {
        int sum = 0;
        for (int j = i; j < i + k; ++j) {
            sum += dp[j][j];
        }
        max_beauty = fmax(max_beauty, sum);
    }

    printf("%d\n", max_beauty);

    return 0;
}