#include <stdio.h>

typedef long long ll;

// 矩阵乘法
void matrix_multiply(ll a[2][2], ll b[2][2], ll m) {
    ll res[2][2] = {{0, 0}, {0, 0}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % m;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            a[i][j] = res[i][j];
        }
    }
}

// 矩阵快速幂
void matrix_power(ll base[2][2], ll n, ll m) {
    ll res[2][2] = {{1, 0}, {0, 1}};
    while (n > 0) {
        if (n & 1) {
            matrix_multiply(res, base, m);
        }
        matrix_multiply(base, base, m);
        n >>= 1;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            base[i][j] = res[i][j];
        }
    }
}

int main() {
    ll p, q, a1, a2, n, m;
    scanf("%lld %lld %lld %lld %lld %lld", &p, &q, &a1, &a2, &n, &m);

    if (n == 1) {
        printf("%lld\n", a1 % m);
        return 0;
    }
    if (n == 2) {
        printf("%lld\n", a2 % m);
        return 0;
    }

    ll base[2][2] = {{p, q}, {1, 0}};
    matrix_power(base, n - 2, m);

    ll result = (base[0][0] * a2 + base[0][1] * a1) % m;
    printf("%lld\n", result);

    return 0;
}