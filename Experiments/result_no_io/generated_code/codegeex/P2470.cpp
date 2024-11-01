#include <stdio.h>
#include <string.h>

#define MAX_LEN 51

int dp[MAX_LEN][MAX_LEN];
char s[MAX_LEN];

int compress(int left, int right) {
    if (dp[left][right] != -1) {
        return dp[left][right];
    }

    if (left > right) {
        return 0;
    }

    dp[left][right] = right - left + 1; // 初始情况下，最短长度就是所有字符的个数

    for (int i = left; i <= right; i++) {
        if (s[i] == 'M') {
            for (int j = i + 1; j <= right; j++) {
                if (s[j] == 'R') {
                    int len = compress(left, i - 1) + compress(i + 1, j - 1);
                    if (len < dp[left][right]) {
                        dp[left][right] = len;
                    }
                }
            }
        }
    }

    return dp[left][right];
}

int main() {
    scanf("%s", s);
    int n = strlen(s);
    memset(dp, -1, sizeof(dp));
    printf("%d\n", compress(0, n - 1));
    return 0;
}