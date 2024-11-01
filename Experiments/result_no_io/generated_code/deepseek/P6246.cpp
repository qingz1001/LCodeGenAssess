#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500000
#define MAXM 500000

int n, m;
int a[MAXN];
long long dp[MAXM][MAXN];
int cost[MAXN][MAXN];

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void preprocess() {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int mid = (i + j) / 2;
            cost[i][j] = 0;
            for (int k = i; k <= j; k++) {
                cost[i][j] += abs(a[k] - a[mid]);
            }
        }
    }
}

void solve() {
    for (int i = 0; i < n; i++) {
        dp[1][i] = cost[0][i];
    }

    for (int i = 2; i <= m; i++) {
        for (int j = i - 1; j < n; j++) {
            dp[i][j] = LLONG_MAX;
            for (int k = i - 2; k < j; k++) {
                if (dp[i - 1][k] + cost[k + 1][j] < dp[i][j]) {
                    dp[i][j] = dp[i - 1][k] + cost[k + 1][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), cmp);
    preprocess();
    solve();

    printf("%lld\n", dp[m][n - 1]);
    return 0;
}