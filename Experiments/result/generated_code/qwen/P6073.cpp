#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

void multiply(int *a, int *b, int len) {
    for (int i = 0; i < len; ++i) {
        a[i] = ((long long)a[i] * b[i]) % MOD;
    }
}

void power(int *a, int p, int len) {
    int result[len];
    for (int i = 0; i < len; ++i) {
        result[i] = (i == 0);
    }
    while (p > 0) {
        if (p & 1) {
            multiply(result, a, len);
        }
        multiply(a, a, len);
        p >>= 1;
    }
    for (int i = 0; i < len; ++i) {
        a[i] = result[i];
    }
}

void factorial(int *a, int len) {
    a[0] = 1;
    for (int i = 1; i < len; ++i) {
        a[i] = (a[i - 1] * i) % MOD;
    }
}

void inverse_factorial(int *a, int len) {
    int inv[len];
    inv[len - 1] = mod_inverse(a[len - 1], MOD);
    for (int i = len - 2; i >= 0; --i) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
    for (int i = 0; i < len; ++i) {
        a[i] = (a[i] * inv[i]) % MOD;
    }
}

int main() {
    int op;
    scanf("%d", &op);

    if (op == 1) {
        int n, q;
        scanf("%d %d", &n, &q);
        int g[n + 1];
        for (int i = 0; i <= n; ++i) {
            g[i] = (i < n) ? 1 : 0;
        }

        for (int i = 0; i < q; ++i) {
            int m;
            scanf("%d", &m);
            int f[n + 1];
            for (int j = 0; j <= n; ++j) {
                f[j] = (j < m) ? 0 : 1;
            }
            multiply(g, f, n + 1);
            printf("%d\n", f[n]);
        }
    } else {
        int q;
        scanf("%d", &q);
        for (int i = 0; i < q; ++i) {
            int n, m;
            scanf("%d %d", &n, &m);
            int g[n + 1];
            int h[n + 1];

            if (op == 2 || op == 3) {
                factorial(g, n + 1);
                inverse_factorial(g, n + 1);
                for (int j = 0; j <= n; ++j) {
                    g[j] = (j < m) ? 0 : (1LL * g[j] * (-1) % MOD + MOD) % MOD;
                }

                for (int j = 0; j <= n; ++j) {
                    h[j] = (j < m) ? 0 : (1LL * g[j] * (-1) % MOD + MOD) % MOD;
                }
            } else if (op == 4) {
                factorial(g, n + 1);
                inverse_factorial(g, n + 1);
                for (int j = 0; j <= n; ++j) {
                    g[j] = (j < m) ? 0 : (1LL * g[j] * (j - m) % MOD + MOD) % MOD;
                }

                factorial(h, n + 1);
                inverse_factorial(h, n + 1);
                for (int j = 0; j <= n; ++j) {
                    h[j] = (j < m) ? 0 : (1LL * h[j] * (-1) % MOD + MOD) % MOD;
                }
            } else if (op == 5) {
                // Implement the fifth subtask logic here
            }

            int f[n + 1];
            for (int j = 0; j <= n; ++j) {
                f[j] = 0;
            }
            for (int j = 0; j <= n; ++j) {
                f[j] = (f[j] + 1LL * g[j] * h[n - j] % MOD) % MOD;
            }

            printf("%d\n", f[n]);
        }
    }

    return 0;
}