#include <stdio.h>
#include <string.h>

int minInsertions(char *s) {
    int n = strlen(s);
    int dp[n][n];

    for (int gap = 0; gap < n; ++gap) {
        for (int i = 0, j = gap; j < n; ++i, ++j) {
            if (gap == 0) {
                dp[i][j] = 0;
            } else if (gap == 1) {
                dp[i][j] = s[i] != s[j];
            } else {
                dp[i][j] = (s[i] == s[j]) ? dp[i + 1][j - 1] : (dp[i + 1][j] < dp[i][j - 1] ? dp[i + 1][j] : dp[i][j - 1]) + 1;
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    char s[1001];
    scanf("%s", s);
    printf("%d\n", minInsertions(s));
    return 0;
}