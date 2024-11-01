#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2005
#define INF 1e18

long long dp[MAX_N];
int r[MAX_N];
int p, m, f, n, s;

long long min(long long a, long long b) {
    return a < b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &r[i]);
    }

    scanf("%d %d %d %d %d", &p, &m, &f, &n, &s);

    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 1; i <= N; i++) {
        long long need = r[i];
        for (int j = 0; j < i; j++) {
            long long cost = dp[j];
            long long remain = need;

            if (i - j >= n) {
                long long slowWash = (i - j - n + 1) * r[j];
                if (slowWash > remain) slowWash = remain;
                cost += slowWash * s;
                remain -= slowWash;
            }

            if (i - j >= m) {
                long long fastWash = (i - j - m + 1) * r[j];
                if (fastWash > remain) fastWash = remain;
                cost += fastWash * f;
                remain -= fastWash;
            }

            cost += remain * p;
            dp[i] = min(dp[i], cost);
        }
    }

    printf("%lld\n", dp[N]);

    return 0;
}