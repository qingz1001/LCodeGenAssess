#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll *a, *f, *g, *dp, *sum;
int n;

int main() {
    scanf("%d", &n);
    a = (ll *)malloc(sizeof(ll) * (n + 2));
    f = (ll *)malloc(sizeof(ll) * (n + 2));
    g = (ll *)malloc(sizeof(ll) * (n + 2));
    dp = (ll *)malloc(sizeof(ll) * (n + 2));
    sum = (ll *)malloc(sizeof(ll) * (n + 2));
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }
    int head = 1, tail = 0;
    for (int i = 1; i <= n; i++) {
        while (head <= tail && f[head] < i - 1) head++;
        dp[i] = sum[i - 1] - sum[f[head]];
        while (head <= tail && g[tail] <= dp[i]) tail--;
        f[++tail] = i - 1;
        g[tail] = dp[i];
    }
    int l = 1, r = n;
    ll ans1 = 0, ans2 = 0;
    while (l < r) {
        if (dp[l] < dp[r]) {
            ans1 += a[l];
            l++;
        } else {
            ans1 += a[r];
            r--;
        }
    }
    if (l == r) ans1 += a[l];
    ans2 = sum[n] - ans1;
    printf("%lld %lld\n", ans1, ans2);
    free(a);
    free(f);
    free(g);
    free(dp);
    free(sum);
    return 0;
}