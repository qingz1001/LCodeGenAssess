#include <stdio.h>
#include <string.h>

#define MAX_LEN 1001

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    char s[MAX_LEN];
    int dp[MAX_LEN][MAX_LEN] = {0};
    int len, i, j, l;

    scanf("%s", s);
    len = strlen(s);

    for (l = 2; l <= len; l++) {
        for (i = 0; i < len - l + 1; i++) {
            j = i + l - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i+1][j-1];
            } else {
                dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;
            }
        }
    }

    printf("%d\n", dp[0][len-1]);

    return 0;
}