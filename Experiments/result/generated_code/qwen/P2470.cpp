#include <stdio.h>
#include <string.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int compress(const char *s) {
    int n = strlen(s);
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; ++i) {
        dp[i] = i;
        for (int j = i - 1; j >= 0; --j) {
            if (strcmp(s + j, s + i - 1) == 0) {
                int len = i - j;
                dp[i] = min(dp[i], dp[j] + 2 + (len > 9));
                break;
            }
        }
    }

    return dp[n];
}

int main() {
    char s[51];
    scanf("%s", s);
    printf("%d\n", compress(s));
    return 0;
}