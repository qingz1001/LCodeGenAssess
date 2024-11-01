#include <stdio.h>
#include <stdint.h>

// 快速幂取模函数
uint64_t pow_mod(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// 矩阵乘法
void matrix_multiply(uint64_t a[2][2], uint64_t b[2][2], uint64_t m) {
    uint64_t result[2][2] = {{0}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % m;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            a[i][j] = result[i][j];
        }
    }
}

// 矩阵快速幂
void matrix_pow(uint64_t matrix[2][2], uint64_t n, uint64_t m) {
    uint64_t result[2][2] = {{1, 0}, {0, 1}};
    while (n > 0) {
        if (n & 1) {
            matrix_multiply(result, matrix, m);
        }
        matrix_multiply(matrix, matrix, m);
        n >>= 1;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matrix[i][j] = result[i][j];
        }
    }
}

int main() {
    uint64_t p, q, a1, a2, n, m;
    scanf("%lu %lu %lu %lu %lu %lu", &p, &q, &a1, &a2, &n, &m);

    if (n == 1) {
        printf("%lu\n", a1 % m);
        return 0;
    }
    if (n == 2) {
        printf("%lu\n", a2 % m);
        return 0;
    }

    uint64_t matrix[2][2] = {{p, q}, {1, 0}};
    matrix_pow(matrix, n - 2, m);

    uint64_t result = (matrix[0][0] * a2 + matrix[0][1] * a1) % m;
    printf("%lu\n", result);

    return 0;
}