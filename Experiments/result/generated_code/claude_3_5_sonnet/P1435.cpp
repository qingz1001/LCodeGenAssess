#include <stdio.h>
#include <string.h>

#define MAX_LEN 1001

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    char str[MAX_LEN];
    int dp[MAX_LEN][MAX_LEN] = {0};
    int len, i, j, k;

    scanf("%s", str);
    len = strlen(str);

    for (i = 0; i < len; i++) {
        dp[i][i] = 0;
    }

    for (k = 1; k < len; k++) {
        for (i = 0; i < len - k; i++) {
            j = i + k;
            if (str[i] == str[j]) {
                dp[i][j] = dp[i+1][j-1];
            } else {
                dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;
            }
        }
    }

    printf("%d\n", dp[0][len-1]);

    return 0;
}