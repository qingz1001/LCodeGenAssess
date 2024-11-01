#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2001
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
        for (int j = i - 1; j >= 0; j--) {
            if (i - j > n) break;
            long long cost = 0;
            if (i - j <= m) cost = f;
            else if (i - j <= n) cost = s;
            dp[i] = min(dp[i], dp[j] + need * p);
            if (j > 0) dp[i] = min(dp[i], dp[j] + need * cost);
            need += r[j];
        }
    }

    printf("%lld\n", dp[N]);

    return 0;
}