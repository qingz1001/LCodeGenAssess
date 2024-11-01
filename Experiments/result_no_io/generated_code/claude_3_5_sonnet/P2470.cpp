#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 51
#define INF 1000000000

int dp[MAX_N][MAX_N];
char s[MAX_N];
int n;

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%s", s);
    n = strlen(s);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
    }

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            if (len == 1) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = len;
                for (int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
                }
                for (int k = i; k < j; k++) {
                    if ((j-k+1) % (k-i+1) == 0 && strncmp(s+i, s+k+1, k-i+1) == 0) {
                        int repeat = (j-k+1) / (k-i+1);
                        int compressed = dp[i][k] + 1;
                        if (repeat >= 4) compressed += 1;
                        else if (repeat >= 2) compressed += repeat - 1;
                        dp[i][j] = min(dp[i][j], compressed);
                    }
                }
            }
        }
    }

    printf("%d\n", dp[0][n-1]);
    return 0;
}