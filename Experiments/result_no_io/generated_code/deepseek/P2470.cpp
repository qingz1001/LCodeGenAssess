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

int main() {
    scanf("%s", str + 1);
    int n = strlen(str + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = j - i + 1;
        }
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
            for (int k = i; k < j; k++) {
                int sub_len = k - i + 1;
                if (is_repeat(i, j, sub_len)) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + 1 + (sub_len >= 10 ? 2 : 1));
                }
            }
        }
    }

    printf("%d\n", dp[1][n]);
    return 0;
}