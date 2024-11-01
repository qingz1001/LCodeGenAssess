#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500000
#define MAXM 500000

int n, m;
int a[MAXN];
long long dp[MAXN][2];
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

long long solve() {
    qsort(a, n, sizeof(int), cmp);
    preprocess();

    for (int i = 0; i < n; i++) {
        dp[i][0] = cost[0][i];
    }

    for (int j = 1; j < m; j++) {
        for (int i = 0; i < n; i++) {
            dp[i][j % 2] = LLONG_MAX;
            for (int k = 0; k < i; k++) {
                dp[i][j % 2] = (dp[i][j % 2] < dp[k][(j - 1) % 2] + cost[k + 1][i]) ? dp[i][j % 2] : (dp[k][(j - 1) % 2] + cost[k + 1][i]);
            }
        }
    }

    return dp[n - 1][(m - 1) % 2];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("%lld\n", solve());

    return 0;
}