#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000005

long long dp[MAX_N][2];
int a[MAX_N];
int n;

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    memset(dp, 0, sizeof(dp));

    for (int len = 1; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            if (len == 1) {
                dp[i][0] = a[i];
                dp[i][1] = 0;
            } else if (len == 2) {
                dp[i][0] = max(a[i], a[j]);
                dp[i][1] = min(a[i], a[j]);
            } else {
                if (a[i] == 0 && a[j] == 0) {
                    dp[i][0] = dp[i+1][1];
                    dp[i][1] = dp[i+1][0];
                } else if (a[i] == 0) {
                    dp[i][0] = dp[i+1][1] + a[j];
                    dp[i][1] = dp[i+1][0];
                } else if (a[j] == 0) {
                    dp[i][0] = dp[i+1][1] + a[i];
                    dp[i][1] = dp[i+1][0];
                } else {
                    long long take_left = a[i] + dp[i+2][1];
                    long long take_right = a[j] + dp[i+1][1];
                    if (take_left > take_right) {
                        dp[i][0] = take_left;
                        dp[i][1] = dp[i+2][0];
                    } else {
                        dp[i][0] = take_right;
                        dp[i][1] = dp[i+1][0];
                    }
                }
            }
        }
    }

    printf("%lld %lld\n", dp[1][0], dp[1][1]);

    return 0;
}