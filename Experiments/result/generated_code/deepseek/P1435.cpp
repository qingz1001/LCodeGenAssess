#include <stdio.h>
#include <string.h>

#define MAX_LEN 1001

int min(int a, int b) {
    return a < b ? a : b;
}

int minInsertionsToPalindrome(char *s) {
    int n = strlen(s);
    int dp[MAX_LEN][MAX_LEN];

    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1];
            } else {
                dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    char s[MAX_LEN];
    scanf("%s", s);
    printf("%d\n", minInsertionsToPalindrome(s));
    return 0;
}