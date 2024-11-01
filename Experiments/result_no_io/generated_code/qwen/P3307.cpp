#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n;
        int a;
        scanf("%lld %d", &n, &a);

        if (a == 1) {
            printf("0\n");
            continue;
        }

        int *dp = (int *)malloc((a + 1) * sizeof(int));
        for (int i = 0; i <= a; i++) {
            dp[i] = 0;
        }

        dp[1] = 1;

        for (long long i = 2; i <= n; i++) {
            int *new_dp = (int *)malloc((a + 1) * sizeof(int));
            for (int j = 0; j <= a; j++) {
                new_dp[j] = 0;
            }

            for (int j = 1; j <= a; j++) {
                for (int k = 1; k <= a; k++) {
                    if (gcd(gcd(j, k), j - k) == 1 && j != k) {
                        new_dp[k] = (new_dp[k] + dp[j]) % MOD;
                    }
                }
            }

            for (int j = 1; j <= a; j++) {
                dp[j] = new_dp[j];
            }

            free(new_dp);
        }

        int result = 0;
        for (int i = 1; i <= a; i++) {
            result = (result + dp[i]) % MOD;
        }

        printf("%d\n", result);
        free(dp);
    }
    return 0;
}