#include <stdio.h>
#include <stdbool.h>

typedef long long ll;

ll n, l, r;
ll a[15];

bool canSumToB(ll b) {
    ll maxVal = b / a[0];
    bool dp[maxVal + 1];
    dp[0] = true;
    for (ll i = 0; i < n; i++) {
        for (ll j = maxVal; j >= 0; j--) {
            if (dp[j] && j + a[i] <= maxVal) {
                dp[j + a[i]] = true;
            }
        }
    }
    return dp[b % a[0]];
}

int main() {
    scanf("%lld %lld %lld", &n, &l, &r);
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    ll count = 0;
    for (ll b = l; b <= r; b++) {
        if (canSumToB(b)) {
            count++;
        }
    }
    printf("%lld\n", count);
    return 0;
}