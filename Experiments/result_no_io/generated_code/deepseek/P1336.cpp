#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 200
#define MAXM 20
#define INF 1e9

int n, m;
int A[MAXM], B[MAXM];
int dp[MAXN + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &A[i], &B[i]);
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
    }
    dp[0] = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= j; k++) {
                dp[j] = min(dp[j], dp[j - k] + A[i] * (int)pow(k, B[i]));
            }
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}