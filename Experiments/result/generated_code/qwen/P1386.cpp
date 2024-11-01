#include <stdio.h>
#include <stdlib.h>

#define MAXN 301
#define MOD 1000000007

int factorial[MAXN];
int inverse[MAXN];

void precompute(int n, int m) {
    factorial[0] = 1;
    for (int i = 1; i <= n; ++i) {
        factorial[i] = (long long)factorial[i - 1] * i % MOD;
    }
    inverse[n] = modInverse(factorial[n], MOD);
    for (int i = n - 1; i >= 0; --i) {
        inverse[i] = (long long)inverse[i + 1] * (i + 1) % MOD;
    }
}

int modInverse(int a, int m) {
    return power(a, m - 2, m);
}

int power(int x, int y, int m) {
    if (y == 0) return 1;
    long long p = power(x, y / 2, m) % m;
    p = (p * p) % m;
    return (y % 2 != 0) ? (int)((p * x) % m) : (int)p;
}

int countArrangements(int n, int m, int *fixed, int *values) {
    int available[MAXN] = {0};
    for (int i = 1; i <= n; ++i) {
        available[i] = 1;
    }
    for (int i = 0; i < m; ++i) {
        available[fixed[i]] = 0;
    }

    int count = 0;
    for (int i = 0; i < m; ++i) {
        if (available[values[i]]) {
            available[values[i]] = 0;
            count++;
        } else {
            break;
        }
    }

    if (count == m) {
        int remaining = n - m;
        return (int)((long long)factorial[remaining] * inverse[count] % MOD);
    } else {
        return 0;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, M;
        scanf("%d %d %d", &n, &m, &M);

        int fixed[m], values[m];
        if (m > 0) {
            for (int i = 0; i < m; ++i) {
                scanf("%d %d", &fixed[i], &values[i]);
            }
        }

        precompute(n, m);

        int result = countArrangements(n, m, fixed, values);
        if (result > 0) {
            printf("YES %d\n", result);
        } else {
            printf("NO\n");
        }
    }
    return 0;
}