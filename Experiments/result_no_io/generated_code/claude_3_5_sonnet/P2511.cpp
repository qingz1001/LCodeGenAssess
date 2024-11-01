#include <stdio.h>
#include <string.h>

#define MAX_N 50001
#define MAX_M 1001
#define MOD 10007

int n, m;
long long L[MAX_N];
long long sum[MAX_N];
long long dp[MAX_N][MAX_M];

long long binary_search(long long left, long long right) {
    while (left < right) {
        long long mid = left + (right - left) / 2;
        int count = 0;
        long long current = 0;
        for (int i = 1; i <= n; i++) {
            if (current + L[i] > mid) {
                count++;
                current = L[i];
            } else {
                current += L[i];
            }
        }
        if (count <= m) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &L[i]);
        sum[i] = sum[i-1] + L[i];
    }

    long long max_length = binary_search(0, sum[n]);

    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m && j < i; j++) {
            long long current = 0;
            for (int k = i; k >= 1; k--) {
                current += L[k];
                if (current > max_length) break;
                if (j > 0) {
                    dp[i][j] = (dp[i][j] + dp[k-1][j-1]) % MOD;
                } else if (k == 1) {
                    dp[i][j] = 1;
                }
            }
        }
    }

    long long count = 0;
    for (int j = 0; j <= m; j++) {
        count = (count + dp[n][j]) % MOD;
    }

    printf("%lld %lld\n", max_length, count);

    return 0;
}