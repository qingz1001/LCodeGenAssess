#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXN 100005

long long phi[MAXN];
long long sum_phi[MAXN];
long long sum_ij_phi[MAXN];

void init() {
    for (int i = 1; i < MAXN; i++) {
        phi[i] = i;
    }
    for (int i = 2; i < MAXN; i++) {
        if (phi[i] == i) {
            for (int j = i; j < MAXN; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    for (int i = 1; i < MAXN; i++) {
        sum_phi[i] = (sum_phi[i-1] + phi[i]) % MOD;
    }
    for (int i = 1; i < MAXN; i++) {
        sum_ij_phi[i] = (sum_ij_phi[i-1] + i * sum_phi[i]) % MOD;
    }
}

long long solve(int n, int m) {
    if (n > m) {
        int temp = n;
        n = m;
        m = temp;
    }
    long long result = 0;
    for (int i = 1; i <= n; i++) {
        result = (result + sum_ij_phi[m / i] * i) % MOD;
    }
    return result;
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        printf("%lld\n", solve(n, m));
    }
    return 0;
}