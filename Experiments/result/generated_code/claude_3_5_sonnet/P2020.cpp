#include <stdio.h>
#include <string.h>

#define MAX_K 1000005
#define MOD 1000000007

typedef long long ll;

ll n, k, p;
ll f[MAX_K];

void multiply(ll a[2][2], ll b[2][2], ll res[2][2]) {
    ll temp[2][2] = {{0}};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                temp[i][j] = (temp[i][j] + a[i][k] * b[k][j]) % p;
    memcpy(res, temp, sizeof(temp));
}

void power(ll base[2][2], ll exp, ll res[2][2]) {
    ll temp[2][2] = {{1, 0}, {0, 1}};
    while (exp > 0) {
        if (exp & 1)
            multiply(temp, base, temp);
        multiply(base, base, base);
        exp >>= 1;
    }
    memcpy(res, temp, sizeof(temp));
}

ll solve(ll n) {
    if (n <= k) return f[n];
    ll matrix[2][2] = {{0, 1}, {1, 1}};
    ll res[2][2];
    power(matrix, n - k, res);
    return (res[1][0] * f[k] % p + res[1][1] * f[k-1] % p) % p;
}

int main() {
    scanf("%lld %lld %lld", &n, &k, &p);

    f[1] = f[2] = 1;
    for (int i = 3; i <= k; i++) {
        f[i] = (f[i-1] + f[i-2]) % p;
        if (f[i] == 1) f[i] = 0;
    }

    printf("%lld\n", solve(n));

    return 0;
}