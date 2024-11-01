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

void manacher(char *s, int n, int *p) {
    int mx = 0, id = 0;
    for (int i = 1; i < n; i++) {
        if (mx > i) {
            p[i] = (p[2 * id - i] < (mx - i) ? p[2 * id - i] : (mx - i));
        } else {
            p[i] = 1;
        }
        while (s[i + p[i]] == s[i - p[i]]) {
            p[i]++;
        }
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
    }
}

int main() {
    int n;
    ll k;
    scanf("%d %lld", &n, &k);
    char s[2000005];
    scanf("%s", s);

    char t[4000005];
    t[0] = '$';
    t[1] = '#';
    int j = 2;
    for (int i = 0; i < n; i++) {
        t[j++] = s[i];
        t[j++] = '#';
    }
    t[j] = '\0';

    int p[4000005];
    memset(p, 0, sizeof(p));
    manacher(t, j, p);

    int count[2000005] = {0};
    for (int i = 2; i < j; i++) {
        int len = p[i] - 1;
        if (len % 2 == 1) {
            count[len]++;
        }
    }

    ll result = 1;
    for (int i = n; i >= 1; i--) {
        if (count[i] > 0) {
            if (k > count[i]) {
                result = (result * power(i, count[i], MOD)) % MOD;
                k -= count[i];
            } else {
                result = (result * power(i, k, MOD)) % MOD;
                k = 0;
                break;
            }
        }
    }

    if (k > 0) {
        printf("-1\n");
    } else {
        printf("%lld\n", result);
    }

    return 0;
}