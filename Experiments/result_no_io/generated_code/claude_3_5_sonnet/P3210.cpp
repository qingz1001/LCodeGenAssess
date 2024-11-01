#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000005
#define max(a, b) ((a) > (b) ? (a) : (b))

long long a[MAX_N];
long long dp[MAX_N][2];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    memset(dp, 0, sizeof(dp));

    for (int i = n; i >= 1; i--) {
        if (a[i] == 0) {
            dp[i][0] = dp[i][1] = 0;
        } else if (i == n || a[i+1] == 0) {
            dp[i][0] = a[i];
            dp[i][1] = 0;
        } else {
            dp[i][0] = max(a[i] + dp[i+1][1], dp[i+1][0]);
            dp[i][1] = dp[i+1][dp[i][0] > dp[i+1][0]];
        }
    }

    long long first = 0, second = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] != 0 && (i == 1 || a[i-1] == 0)) {
            first += dp[i][0];
            second += dp[i][1];
            break;
        }
    }

    printf("%lld %lld\n", first, second);

    return 0;
}