#include <stdio.h>

#define MAXW 30000
#define MOD 1000000007

int dp[MAXW + 1][10];

int main() {
    int k, w;
    scanf("%d %d", &k, &w);

    for (int i = 0; i <= 9; ++i) dp[0][i] = 1;

    for (int len = 1; len <= w; ++len) {
        for (int i = 0; i <= 9; ++i) {
            dp[len][i] = 0;
            for (int j = 0; j < i; ++j) {
                dp[len][i] = (dp[len][i] + dp[len - 1][j]) % MOD;
            }
        }
    }

    long long result = 0;
    for (int i = 1; i <= 9; ++i) {
        if (len * k >= w) {
            result = (result + dp[w][i]) % MOD;
        } else {
            result = (result + dp[w - len * k][i]) % MOD;
        }
    }

    printf("%lld\n", result);
    return 0;
}