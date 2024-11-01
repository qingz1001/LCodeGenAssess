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
    ll temp[2][2] = {0};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                temp[i][j] = mod_add(temp[i][j], mod_mul(A[i][k], B[k][j], p), p);
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            C[i][j] = temp[i][j];
        }
    }
}

void matrix_pow(ll A[2][2], ll n, ll p, ll result[2][2]) {
    ll temp[2][2] = {{1, 0}, {0, 1}};
    while (n > 0) {
        if (n % 2 == 1) {
            matrix_mul(temp, A, temp, p);
        }
        matrix_mul(A, A, A, p);
        n /= 2;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = temp[i][j];
        }
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
    for (int i = 0; i < k; i++) mod_k[i] = -1;
    mod_k[1] = 0;
    for (ll i = 3; i <= n; i++) {
        ll fn = mod_add(f1, f2, k);
        f1 = f2;
        f2 = fn;
        if (fn == 1) {
            period = i - 2;
            break;
        }
        if (mod_k[fn] == -1) {
            mod_k[fn] = i - 2;
        } else {
            period = i - 2 - mod_k[fn];
            break;
        }
    }
    if (period == 0) {
        return fibonacci_mod(n, p);
    } else {
        ll remainder = (n - 2) % period;
        return fibonacci_mod(remainder + 2, p);
    }
}

int main() {
    ll n, k, p;
    scanf("%lld %lld %lld", &n, &k, &p);
    printf("%lld\n", solve(n, k, p));
    return 0;
}