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

void printPreOrder(int l, int r) {
    if (l > r) return;
    printf("%d ", root[l][r] + 1);
    printPreOrder(l, root[l][r] - 1);
    printPreOrder(root[l][r] + 1, r);
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
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            dp[l][r] = -INF;
            for (int k = l; k <= r; k++) {
                long long left = (k > l) ? dp[l][k - 1] : 1;
                long long right = (k < r) ? dp[k + 1][r] : 1;
                long long score = left * right + scores[k];
                if (score > dp[l][r]) {
                    dp[l][r] = score;
                    root[l][r] = k;
                }
            }
        }
    }

    printf("%lld\n", dp[0][n - 1]);
    printPreOrder(0, n - 1);
    printf("\n");

    return 0;
}