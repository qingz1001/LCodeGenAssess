#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005
#define MAXM 5005

int n, m;
int a[MAXM], b[MAXM], c[MAXM];
int dp[MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a[i], &b[i], &c[i]);
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i-1];
        for (int j = 0; j < m; j++) {
            if (i >= a[j]) {
                dp[i] = fmax(dp[i], dp[max(0, i-b[j]-c[j]+1)] + max(0, c[j]));
            }
        }
    }

    printf("%d\n", dp[n]);

    return 0;
}