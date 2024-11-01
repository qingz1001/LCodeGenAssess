#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000001

int n;
int parent[MAXN];
long long a[MAXN], b[MAXN];
long long dp[MAXN];
long long sum_a[MAXN], sum_b[MAXN];

void dfs(int u) {
    for (int i = u; i != -1; i = parent[i]) {
        dp[i] = LLONG_MAX;
        for (int j = u; j != -1; j = parent[j]) {
            long long r = (sum_a[i] - sum_a[j]) * b[j] - (sum_b[i] - sum_b[j]) * a[j];
            r = labs(r) / __gcd((sum_a[i] - sum_a[j]) * b[j], (sum_b[i] - sum_b[j]) * a[j]);
            dp[i] = fmin(dp[i], dp[j] + r);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &parent[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &b[i]);
    }

    for (int i = 1; i <= n; i++) {
        sum_a[i] = sum_a[i - 1] + a[i];
        sum_b[i] = sum_b[i - 1] + b[i];
    }

    dfs(1);

    printf("%lld\n", dp[1]);

    return 0;
}