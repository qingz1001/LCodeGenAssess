#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromeSubseq(char *s) {
    int len = strlen(s);
    int dp[len][len];
    memset(dp, 0, sizeof(dp));

    for (int i = len - 1; i >= 0; i--) {
        dp[i][i] = 1;
        for (int j = i + 1; j < len; j++) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][len - 1];
}

int main() {
    int n;
    scanf("%d", &n);
    char s[10000001];

    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        printf("%d\n", longestPalindromeSubseq(s));
    }

    return 0;
}