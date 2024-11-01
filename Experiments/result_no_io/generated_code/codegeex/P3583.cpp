#include <stdio.h>
#include <math.h>

typedef long long ll;

ll n;
int maxk;
int sqs[100], nsqs;

void init() {
    int i, m = sqrt(n);
    nsqs = 0;
    for (i = 1; i <= m; i++) {
        sqs[nsqs++] = i * i;
    }
}

int dp[100000];

int f(ll x) {
    int i, j, m = sqrt(x);
    for (i = 0; i <= m; i++) dp[i] = 0;
    for (i = 0; i < nsqs; i++) {
        for (j = m; j >= sqs[i]; j--) {
            dp[j] = dp[j - sqs[i]] + 1;
        }
    }
    for (i = m; i >= 0; i--) {
        if (dp[i] && x < (ll)i * i) return i;
    }
    return -1;
}

int main() {
    scanf("%lld", &n);
    init();
    maxk = f(n);
    if (maxk == -1) {
        printf("- %d\n", n);
        return 0;
    }
    printf("%d ", maxk);
    int ans = 0;
    for (ll i = 1; i <= n; i++) {
        if (f(i) != maxk) ans++;
    }
    printf("%d\n", ans);
    return 0;
}