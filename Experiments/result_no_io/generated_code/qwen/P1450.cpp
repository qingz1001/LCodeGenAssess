#include <stdio.h>

#define MAX_N 1000
#define MAX_S 100000

int main() {
    int c1, c2, c3, c4, n;
    scanf("%d %d %d %d %d", &c1, &c2, &c3, &c4, &n);

    for (int i = 0; i < n; ++i) {
        int d1, d2, d3, d4, s;
        scanf("%d %d %d %d %d", &d1, &d2, &d3, &d4, &s);

        long long dp[MAX_S + 1] = {0};
        dp[0] = 1;

        for (int j = 1; j <= d1 && j * c1 <= s; ++j) {
            dp[j * c1] += 1;
        }
        for (int j = 1; j <= d2 && j * c2 <= s; ++j) {
            dp[j * c2] += 1;
        }
        for (int j = 1; j <= d3 && j * c3 <= s; ++j) {
            dp[j * c3] += 1;
        }
        for (int j = 1; j <= d4 && j * c4 <= s; ++j) {
            dp[j * c4] += 1;
        }

        for (int j = c1; j <= s; ++j) {
            if (dp[j - c1] > 0) {
                dp[j] += dp[j - c1];
            }
        }
        for (int j = c2; j <= s; ++j) {
            if (dp[j - c2] > 0) {
                dp[j] += dp[j - c2];
            }
        }
        for (int j = c3; j <= s; ++j) {
            if (dp[j - c3] > 0) {
                dp[j] += dp[j - c3];
            }
        }
        for (int j = c4; j <= s; ++j) {
            if (dp[j - c4] > 0) {
                dp[j] += dp[j - c4];
            }
        }

        printf("%lld\n", dp[s]);
    }

    return 0;
}