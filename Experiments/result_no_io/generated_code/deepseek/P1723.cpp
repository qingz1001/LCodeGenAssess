#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int longestPalindrome(char* s) {
    int n = strlen(s);
    if (n == 0) return 0;

    int maxLen = 1;
    int start = 0;
    int dp[n][n];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
        if (i < n - 1 && s[i] == s[i + 1]) {
            dp[i][i + 1] = 1;
            maxLen = 2;
            start = i;
        }
    }

    for (int len = 3; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = 1;
                maxLen = len;
                start = i;
            }
        }
    }

    return maxLen;
}

int main() {
    int n;
    scanf("%d", &n);
    char s[10000000];

    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        printf("%d\n", longestPalindrome(s));
    }

    return 0;
}