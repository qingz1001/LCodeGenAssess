#include <stdio.h>
#include <string.h>

#define MAX_N 1001
#define MOD 1000000007

int dp[MAX_N];
int count[MAX_N];

int main() {
    int n;
    scanf("%d", &n);

    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    count[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= i; j--) {
            if (dp[j] > dp[j - i] + 1) {
                dp[j] = dp[j - i] + 1;
                count[j] = count[j - i];
            } else if (dp[j] == dp[j - i] + 1) {
                count[j] = (count[j] + count[j - i]) % MOD;
            }
        }
    }

    printf("%d %d\n", dp[n], count[n]);

    return 0;
}