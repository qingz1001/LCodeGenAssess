#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll mod_add(ll a, ll b, ll p) {
    return (a + b) % p;
}

ll mod_sub(ll a, ll b, ll p) {
    return (a - b + p) % p;
}

ll mod_mul(ll a, ll b, ll p) {
    return (a * b) % p;
}

void matrix_mul(ll A[2][2], ll B[2][2], ll C[2][2], ll p) {
    ll temp[2][2];
    temp[0][0] = mod_add(mod_mul(A[0][0], B[0][0], p), mod_mul(A[0][1], B[1][0], p), p);
    temp[0][1] = mod_add(mod_mul(A[0][0], B[0][1], p), mod_mul(A[0][1], B[1][1], p), p);
    temp[1][0] = mod_add(mod_mul(A[1][0], B[0][0], p), mod_mul(A[1][1], B[1][0], p), p);
    temp[1][1] = mod_add(mod_mul(A[1][0], B[0][1], p), mod_mul(A[1][1], B[1][1], p), p);
    C[0][0] = temp[0][0];
    C[0][1] = temp[0][1];
    C[1][0] = temp[1][0];
    C[1][1] = temp[1][1];
}

void matrix_pow(ll A[2][2], ll n, ll p, ll result[2][2]) {
    ll temp[2][2];
    result[0][0] = 1;
    result[0][1] = 0;
    result[1][0] = 0;
    result[1][1] = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            matrix_mul(result, A, temp, p);
            result[0][0] = temp[0][0];
            result[0][1] = temp[0][1];
            result[1][0] = temp[1][0];
            result[1][1] = temp[1][1];
        }
        matrix_mul(A, A, temp, p);
        A[0][0] = temp[0][0];
        A[0][1] = temp[0][1];
        A[1][0] = temp[1][0];
        A[1][1] = temp[1][1];
        n /= 2;
    }
}

ll fibonacci_mod(ll n, ll p) {
    if (n == 1 || n == 2) return 1;
    ll A[2][2] = {{1, 1}, {1, 0}};
    ll result[2][2];
    matrix_pow(A, n - 2, p, result);
    return mod_add(result[0][0], result[0][1], p);
}

ll solve(ll n, ll k, ll p) {
    ll f1 = 1, f2 = 1;
    ll period = 0;
    ll mod_k[k];
    for (ll i = 0; i < k; i++) mod_k[i] = -1;
    mod_k[1] = 0;
    for (ll i = 3; ; i++) {
        ll fn = mod_add(f1, f2, k);
        f1 = f2;
        f2 = fn;
        ll mod = fn % k;
        if (mod_k[mod] != -1) {
            period = i - mod_k[mod];
            break;
        }
        mod_k[mod] = i;
    }
    ll actual_n = n % period;
    if (actual_n == 0) actual_n = period;
    return fibonacci_mod(actual_n, p);
}

int main() {
    ll n, k, p;
    scanf("%lld %lld %lld", &n, &k, &p);
    printf("%lld\n", solve(n, k, p));
    return 0;
}