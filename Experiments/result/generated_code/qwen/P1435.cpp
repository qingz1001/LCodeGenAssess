#include <stdio.h>
#include <string.h>

int minInsertions(char *s) {
    int n = strlen(s);
    int dp[n][n];
    
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            if (len == 1) {
                dp[i][j] = 0;
            } else if (len == 2) {
                dp[i][j] = (s[i] != s[j]);
            } else {
                dp[i][j] = (s[i] == s[j]) ? dp[i+1][j-1] : (1 + (dp[i+1][j] < dp[i][j-1] ? dp[i+1][j] : dp[i][j-1]));
            }
        }
    }
    
    return dp[0][n-1];
}

int main() {
    char s[1005];
    scanf("%s", s);
    printf("%d\n", minInsertions(s));
    return 0;
}