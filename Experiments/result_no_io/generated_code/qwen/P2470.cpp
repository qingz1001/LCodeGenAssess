#include <stdio.h>
#include <string.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int compress_length(char *s) {
    int n = strlen(s);
    if (n <= 1) return n;

    int dp[n + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1] + 1;
        char buffer[51];
        strncpy(buffer, s + i - dp[i], dp[i]);
        buffer[dp[i]] = '\0';

        for (int j = 0; j < i - dp[i]; j++) {
            if (strncmp(s + j, buffer, dp[i]) == 0) {
                dp[i] = min(dp[i], j + 1 + 1 + dp[j]);
                break;
            }
        }

        if (i > 1 && s[i - 1] != s[i - 2]) {
            dp[i] = min(dp[i], dp[i - 2] + 2);
        }
    }

    return dp[n];
}

int main() {
    char s[51];
    scanf("%s", s);
    printf("%d\n", compress_length(s));
    return 0;
}