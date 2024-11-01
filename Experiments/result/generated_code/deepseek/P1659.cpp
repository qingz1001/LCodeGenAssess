#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 19930726

typedef long long ll;

ll power(ll base, ll exp, ll mod) {
    ll result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int n, K;
    scanf("%d %d", &n, &K);
    char s[1000005];
    scanf("%s", s);

    int p[1000005];
    int mx = 0, id = 0;
    for (int i = 0; i < n; i++) {
        p[i] = mx > i ? (p[2 * id - i] < mx - i ? p[2 * id - i] : mx - i) : 1;
        while (i - p[i] >= 0 && i + p[i] < n && s[i - p[i]] == s[i + p[i]]) p[i]++;
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
    }

    ll count[1000005] = {0};
    for (int i = 0; i < n; i++) {
        count[p[i] * 2 - 1]++;
    }

    ll total = 0;
    ll result = 1;
    for (int i = n; i > 0; i -= 2) {
        if (count[i] > 0) {
            if (total + count[i] <= K) {
                result = (result * power(i, count[i], MOD)) % MOD;
                total += count[i];
            } else {
                result = (result * power(i, K - total, MOD)) % MOD;
                total = K;
                break;
            }
        }
    }

    if (total < K) {
        printf("-1\n");
    } else {
        printf("%lld\n", result);
    }

    return 0;
}