#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint64_t a, b, c, d;
} Matrix;

uint64_t m_global;

Matrix multiply(Matrix x, Matrix y) {
    Matrix res;
    res.a = (x.a * y.a + x.b * y.c) % m_global;
    res.b = (x.a * y.b + x.b * y.d) % m_global;
    res.c = (x.c * y.a + x.d * y.c) % m_global;
    res.d = (x.c * y.b + x.d * y.d) % m_global;
    return res;
}

Matrix power(Matrix base, uint64_t exp) {
    Matrix result = {1, 0, 0, 1};
    while (exp > 0) {
        if (exp & 1)
            result = multiply(result, base);
        base = multiply(base, base);
        exp >>= 1;
    }
    return result;
}

int main(){
    uint64_t p, q, a1, a2, n, m;
    scanf("%llu %llu %llu %llu %llu %llu", &p, &q, &a1, &a2, &n, &m);
    m_global = m;
    if(n == 1){
        printf("%llu\n", a1 % m);
        return 0;
    }
    if(n == 2){
        printf("%llu\n", a2 % m);
        return 0;
    }
    Matrix base = {p % m, q % m, 1, 0};
    Matrix res = power(base, n - 2);
    uint64_t ans = (res.a * a2 + res.b * a1) % m;
    printf("%llu\n", ans);
    return 0;
}