#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500

int min(int a, int b) {
    return a < b ? a : b;
}

int dp[MAXN][MAXN];
int beads[MAXN];

int solve(int l, int r) {
    if (l > r) return 0;
    if (dp[l][r] != -1) return dp[l][r];

    int res = 1 + solve(l + 1, r); // 直接在l位置插入一个与beads[l]相同的珠子

    for (int i = l + 1; i <= r; i++) {
        if (beads[i] == beads[l]) {
            res = min(res, solve(l + 1, i - 1) + solve(i, r));
        }
    }

    dp[l][r] = res;
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &beads[i]);
    }

    memset(dp, -1, sizeof(dp));

    printf("%d\n", solve(0, n - 1));

    return 0;
}