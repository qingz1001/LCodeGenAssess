#include <stdio.h>
#include <stdlib.h>

#define MAXN 30001
#define MAXM 5001

int n, m;
int a[MAXM], b[MAXM], c[MAXM];
int dp[MAXN];

void merge(int l, int r) {
    for (int i = l; i <= r; i++) {
        dp[i] += dp[i - 1];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a[i], &b[i], &c[i]);
        dp[a[i]]++;
        if (b[i] + 1 <= n) {
            dp[b[i] + 1]--;
        }
    }

    merge(1, n);

    int result = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] >= c[i]) {
            result += dp[i] - c[i];
            dp[i] = c[i];
        }
    }

    printf("%d\n", result);
    return 0;
}