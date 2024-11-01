#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30
#define INF 4000000000

int n;
int scores[MAXN];
long long dp[MAXN][MAXN];
int root[MAXN][MAXN];

long long max(long long a, long long b) {
    return a > b ? a : b;
}

void printPreorder(int l, int r) {
    if (l > r) return;
    printf("%d ", root[l][r] + 1);
    printPreorder(l, root[l][r] - 1);
    printPreorder(root[l][r] + 1, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &scores[i]);
    }

    for (int i = 0; i < n; i++) {
        dp[i][i] = scores[i];
        root[i][i] = i;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            dp[i][j] = -INF;
            for (int k = i; k <= j; k++) {
                long long left = (k > i) ? dp[i][k - 1] : 1;
                long long right = (k < j) ? dp[k + 1][j] : 1;
                long long score = left * right + scores[k];
                if (score > dp[i][j]) {
                    dp[i][j] = score;
                    root[i][j] = k;
                }
            }
        }
    }

    printf("%lld\n", dp[0][n - 1]);
    printPreorder(0, n - 1);
    printf("\n");

    return 0;
}