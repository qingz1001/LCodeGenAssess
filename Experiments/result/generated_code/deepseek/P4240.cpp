#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353
#define MAXN 100005

typedef long long ll;

ll phi[MAXN];
ll sum_phi[MAXN];

void euler_sieve(int n) {
    for (int i = 1; i <= n; i++) {
        phi[i] = i;
    }
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    sum_phi[0] = 0;
    for (int i = 1; i <= n; i++) {
        sum_phi[i] = (sum_phi[i - 1] + phi[i]) % MOD;
    }
}

ll solve(int n, int m) {
    if (n > m) {
        int temp = n;
        n = m;
        m = temp;
    }
    ll ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = (n / (n / l) < m / (m / l)) ? n / (n / l) : m / (m / l);
        ans = (ans + (sum_phi[r] - sum_phi[l - 1] + MOD) % MOD * (n / l) % MOD * (m / l) % MOD) % MOD;
    }
    return ans;
}

int main() {
    int T, n, m;
    scanf("%d", &T);
    euler_sieve(MAXN - 1);
    while (T--) {
        scanf("%d %d", &n, &m);
        printf("%lld\n", solve(n, m));
    }
    return 0;
}