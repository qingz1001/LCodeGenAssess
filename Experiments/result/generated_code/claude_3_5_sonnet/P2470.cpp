#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 51
#define MIN(a, b) ((a) < (b) ? (a) : (b))

char s[MAX_N];
int dp[MAX_N][MAX_N];

int main() {
    scanf("%s", s);
    int n = strlen(s);

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            dp[i][j] = j - i + 1;
        }
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            
            // Try to compress using 'R'
            for (int k = i; k < j; k++) {
                dp[i][j] = MIN(dp[i][j], dp[i][k] + dp[k+1][j]);
            }
            
            // Try to compress using 'M' and 'R'
            for (int k = i; k <= j; k++) {
                int repeat_len = j - k + 1;
                if (repeat_len <= k - i) {
                    if (strncmp(s + i, s + k, repeat_len) == 0) {
                        dp[i][j] = MIN(dp[i][j], dp[i][k-1] + 2);
                    }
                }
            }
        }
    }

    printf("%d\n", dp[0][n-1]);
    return 0;
}