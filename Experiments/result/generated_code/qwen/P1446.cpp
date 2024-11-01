#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

void multiply(int A[4][4], int B[4][4]) {
    int C[4][4] = {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                C[i][j] = (C[i][j] + (long long)A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            A[i][j] = C[i][j];
        }
    }
}

void power(int A[4][4], int n) {
    int result[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    while (n > 0) {
        if (n & 1) {
            multiply(result, A);
        }
        multiply(A, A);
        n >>= 1;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            A[i][j] = result[i][j];
        }
    }
}

int main() {
    int Sr, Sb, Sg, m, P;
    scanf("%d %d %d %d %d", &Sr, &Sb, &Sg, &m, &P);

    int dp[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    int inv[P];
    inv[1] = 1;
    for (int i = 2; i < P; i++) {
        inv[i] = mod_inverse(i, P);
    }

    for (int i = 0; i < m; i++) {
        int perm[100];
        for (int j = 0; j < Sr + Sb + Sg; j++) {
            scanf("%d", &perm[j]);
        }
        int count[4] = {0};
        for (int j = 0; j < Sr + Sb + Sg; j++) {
            count[perm[j]]++;
        }
        int fact = 1;
        for (int j = 0; j < 4; j++) {
            fact = (fact * factorial[count[j]]) % P;
        }
        for (int j = 0; j < 4; j++) {
            dp[j][count[j]] = (dp[j][count[j]] * fact) % P;
        }
    }

    power(dp, P - 2);

    int result = 0;
    for (int i = 0; i < 4; i++) {
        result = (result + dp[i][0]) % P;
    }

    printf("%d\n", result);

    return 0;
}