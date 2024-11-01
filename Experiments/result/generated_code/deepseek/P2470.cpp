#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 55

int dp[MAXN][MAXN];
char str[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int is_repeat(int l, int r, int len) {
    if ((r - l + 1) % len != 0) return 0;
    for (int i = l; i <= r; i++) {
        if (str[i] != str[(i - l) % len + l]) return 0;
    }
    return 1;
}

int dfs(int l, int r) {
    if (dp[l][r] != -1) return dp[l][r];
    if (l == r) return dp[l][r] = 1;

    int len = r - l + 1;
    dp[l][r] = len;

    for (int i = l; i < r; i++) {
        dp[l][r] = min(dp[l][r], dfs(l, i) + dfs(i + 1, r));
    }

    for (int i = 1; i <= len / 2; i++) {
        if (is_repeat(l, r, i)) {
            dp[l][r] = min(dp[l][r], dfs(l, l + i - 1) + 1 + (l != 0));
        }
    }

    return dp[l][r];
}

int main() {
    scanf("%s", str);
    int n = strlen(str);
    memset(dp, -1, sizeof(dp));
    printf("%d\n", dfs(0, n - 1));
    return 0;
}