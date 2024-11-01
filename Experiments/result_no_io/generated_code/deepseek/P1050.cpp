#include <stdio.h>
#include <string.h>

#define MAX_K 100
#define MOD 1000000000000000000ULL // 10^18

typedef unsigned long long ull;

void multiply(ull F[2][2], ull M[2][2]) {
    ull x = (F[0][0] * M[0][0] % MOD + F[0][1] * M[1][0] % MOD) % MOD;
    ull y = (F[0][0] * M[0][1] % MOD + F[0][1] * M[1][1] % MOD) % MOD;
    ull z = (F[1][0] * M[0][0] % MOD + F[1][1] * M[1][0] % MOD) % MOD;
    ull w = (F[1][0] * M[0][1] % MOD + F[1][1] * M[1][1] % MOD) % MOD;

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void power(ull F[2][2], ull n) {
    if (n == 0 || n == 1) return;
    ull M[2][2] = {{1, 1}, {1, 0}};

    power(F, n / 2);
    multiply(F, F);

    if (n % 2 != 0) multiply(F, M);
}

ull fib(ull n) {
    ull F[2][2] = {{1, 1}, {1, 0}};
    if (n == 0) return 0;
    power(F, n - 1);
    return F[0][0];
}

int main() {
    ull n, k;
    scanf("%llu %llu", &n, &k);

    if (k == 1) {
        printf("1\n");
        return 0;
    }

    ull last_k_digits = n % MOD;
    ull current = last_k_digits;
    ull cycle_length = 0;
    ull seen[MAX_K + 1];
    memset(seen, 0, sizeof(seen));

    for (ull i = 1; i <= MOD; i++) {
        current = (current * last_k_digits) % MOD;
        if (seen[current % (1 << k)] != 0) {
            cycle_length = i - seen[current % (1 << k)];
            break;
        }
        seen[current % (1 << k)] = i;
    }

    if (cycle_length == 0) {
        printf("-1\n");
    } else {
        printf("%llu\n", cycle_length);
    }

    return 0;
}