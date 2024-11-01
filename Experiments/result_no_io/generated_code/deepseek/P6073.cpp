#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long mod_inv(long long x, long long mod) {
    return mod_pow(x, mod - 2, mod);
}

long long factorial[1000001];

void precompute_factorials(int max_n) {
    factorial[0] = 1;
    for (int i = 1; i <= max_n; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
}

long long binomial_coefficient(int n, int k) {
    if (k > n) return 0;
    return (factorial[n] * mod_inv((factorial[k] * factorial[n - k]) % MOD, MOD)) % MOD;
}

long long solve_subtask1(int n, int m) {
    if (m > n) return 0;
    return mod_pow(m, n, MOD);
}

long long solve_subtask2_3(int n, int m) {
    long long result = 0;
    for (int k = m; k <= n; k++) {
        long long g_k = mod_inv(factorial[k + m + 1], MOD);
        long long h_k = (k - m) % 2 == 0 ? 1 : -1;
        h_k = (h_k * mod_inv(factorial[k - m], MOD)) % MOD;
        result = (result + (mod_pow(k, n, MOD) * g_k % MOD * h_k % MOD)) % MOD;
    }
    return (result + MOD) % MOD;
}

long long solve_subtask4(int n, int m) {
    long long result = 0;
    for (int k = 0; k <= n; k++) {
        long long g_k = (mod_pow(k, m, MOD) * mod_inv(factorial[k], MOD)) % MOD;
        long long h_k = (k % 2 == 0 ? 1 : -1) * mod_inv(factorial[k], MOD);
        result = (result + (mod_pow(k, n, MOD) * g_k % MOD * h_k % MOD)) % MOD;
    }
    return (result + MOD) % MOD;
}

long long solve_subtask5(int n, int m) {
    long long result = 0;
    for (int k = 0; k <= m; k++) {
        long long term1 = mod_pow(k + 1, m, MOD);
        long long term2 = mod_pow(k + 1, n + 1, MOD);
        long long term3 = mod_inv(factorial[k + 1], MOD);
        for (int i = 0; i <= m - k; i++) {
            long long term4 = binomial_coefficient(2 * n + 1, i);
            long long term5 = (i % 2 == 0 ? 1 : -1) * mod_inv(factorial[m - k - i], MOD);
            long long term6 = mod_inv(mod_pow(k + 1, i, MOD), MOD);
            result = (result + (term1 * term2 % MOD * term3 % MOD * term4 % MOD * term5 % MOD * term6 % MOD)) % MOD;
        }
    }
    return (result + MOD) % MOD;
}

int main() {
    int op;
    scanf("%d", &op);

    if (op == 1) {
        int n, q;
        scanf("%d %d", &n, &q);
        precompute_factorials(n);
        while (q--) {
            int m;
            scanf("%d", &m);
            printf("%lld\n", solve_subtask1(n, m));
        }
    } else if (op == 2 || op == 3) {
        int q;
        scanf("%d", &q);
        while (q--) {
            int n, m;
            scanf("%d %d", &n, &m);
            printf("%lld\n", solve_subtask2_3(n, m));
        }
    } else if (op == 4) {
        int q;
        scanf("%d", &q);
        while (q--) {
            int n, m;
            scanf("%d %d", &n, &m);
            printf("%lld\n", solve_subtask4(n, m));
        }
    } else if (op == 5) {
        int q;
        scanf("%d", &q);
        while (q--) {
            int n, m;
            scanf("%d %d", &n, &m);
            printf("%lld\n", solve_subtask5(n, m));
        }
    }

    return 0;
}