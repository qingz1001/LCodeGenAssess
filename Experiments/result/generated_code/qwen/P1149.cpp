#include <stdio.h>

#define MAX_N 25

int matches[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int dp[MAX_N][MAX_N];

int main() {
    int n;
    scanf("%d", &n);

    if (n % 2 != 0 || n < 4) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            int k = i - j;
            if (k == j) {
                dp[i][j] = (i >= 2 && j >= 2);
            } else {
                dp[i][j] = 0;
                for (int a = 0; a <= 9; ++a) {
                    if (matches[a] > i) break;
                    if (dp[i - matches[a]][j]) {
                        dp[i][j] += dp[i - matches[a]][j];
                    }
                }
                for (int b = 0; b <= 9; ++b) {
                    if (matches[b] > k) break;
                    if (dp[k - matches[b]][j]) {
                        dp[i][j] += dp[k - matches[b]][j];
                    }
                }
            }
        }
    }

    int result = 0;
    for (int a = 0; a <= 9; ++a) {
        if (matches[a] * 2 > n) break;
        for (int b = 0; b <= 9; ++b) {
            if (matches[b] * 2 > n) break;
            int c = n - 2 * matches[a] - 2 * matches[b];
            if (c >= 0 && matches[c] == c) {
                result += dp[n - 2 * matches[a] - 2 * matches[b]][a];
            }
        }
    }

    printf("%d\n", result);
    return 0;
}