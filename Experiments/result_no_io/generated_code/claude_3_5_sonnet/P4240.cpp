#include <stdio.h>
#include <string.h>

#define MAX 100001
#define MOD 998244353

long long phi[MAX], sum_phi[MAX];

void init() {
    for (int i = 1; i < MAX; i++) {
        phi[i] = i;
    }
    for (int i = 2; i < MAX; i++) {
        if (phi[i] == i) {
            for (int j = i; j < MAX; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    for (int i = 1; i < MAX; i++) {
        sum_phi[i] = (sum_phi[i-1] + phi[i]) % MOD;
    }
}

long long solve(int n, int m) {
    long long result = 0;
    for (int i = 1; i <= n; i++) {
        result = (result + sum_phi[m] * i % MOD) % MOD;
    }
    return result;
}

int main() {
    init();
    int T, n, m;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        printf("%lld\n", solve(n, m));
    }
    return 0;
}