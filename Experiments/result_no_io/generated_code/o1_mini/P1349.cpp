#include <stdio.h>
typedef unsigned long long ull;

typedef struct {
    ull a, b, c, d;
} matrix;

matrix mul(matrix x, matrix y, ull m){
    matrix res;
    res.a = (x.a * y.a + x.b * y.c) % m;
    res.b = (x.a * y.b + x.b * y.d) % m;
    res.c = (x.c * y.a + x.d * y.c) % m;
    res.d = (x.c * y.b + x.d * y.d) % m;
    return res;
}

matrix power_matrix(matrix x, ull e, ull m){
    matrix res;
    res.a = 1 % m;
    res.b = 0;
    res.c = 0;
    res.d = 1 % m;
    while(e > 0){
        if(e & 1){
            res = mul(res, x, m);
        }
        x = mul(x, x, m);
        e >>= 1;
    }
    return res;
}

int main(){
    ull p, q, a1, a2, n, m;
    scanf("%llu %llu %llu %llu %llu %llu", &p, &q, &a1, &a2, &n, &m);
    if(m == 1){
        printf("0\n");
        return 0;
    }
    if(n == 1){
        printf("%llu\n", a1 % m);
        return 0;
    }
    if(n == 2){
        printf("%llu\n", a2 % m);
        return 0;
    }
    matrix trans;
    trans.a = p % m;
    trans.b = q % m;
    trans.c = 1;
    trans.d = 0;
    matrix res = power_matrix(trans, n - 2, m);
    ull an = (res.a * a2 + res.b * a1) % m;
    printf("%llu\n", an);
    return 0;
}