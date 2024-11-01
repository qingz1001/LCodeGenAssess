#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define BASE 26
#define MOD 1000000007

typedef long long ll;

ll power(ll a, ll b) {
    ll result = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % MOD;
        }
        a = (a * a) % MOD;
        b /= 2;
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    char s[MAXN];
    scanf("%s", s);

    ll cnt[BASE] = {0};
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int c = s[j] - 'a';
            if (cnt[c] == 0) {
                ans = (ans + 1) % MOD;
            }
            cnt[c]++;
        }
        memset(cnt, 0, sizeof(cnt));
    }

    printf("%lld\n", ans);
    return 0;
}