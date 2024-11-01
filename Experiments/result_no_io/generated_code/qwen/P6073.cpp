#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353

typedef long long ll;

ll mod_pow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll mod_inv(ll a) {
    return mod_pow(a, MOD - 2);
}

void fft(int n, int sign, complex<double> *a) {
    for (int i = 1, j; i < n; ++i) {
        for (j = n >> 1; j & i; j >>= 1);
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = sign * 2 * M_PI / len;
        complex<double> wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            complex<double> w(1);
            for (int j = 0; j < len / 2; ++j) {
                complex<double> u = a[i + j];
                complex<double> v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (sign == -1) {
        for (int i = 0; i < n; ++i)
            a[i] /= n;
    }
}

void ntt(int n, int sign, vector<ll> &a) {
    vector<complex<double>> A(n);
    for (int i = 0; i < n; ++i)
        A[i] = a[i];
    fft(n, sign, A.begin());
    for (int i = 0; i < n; ++i)
        a[i] = round(A[i].real() + 0.5);
}

vector<ll> multiply(vector<ll> &a, vector<ll> &b) {
    int n = 1;
    while (n < a.size() || n < b.size())
        n <<= 1;
    vector<ll> fa(n), fb(n);
    for (int i = 0; i < a.size(); ++i)
        fa[i] = a[i];
    for (int i = 0; i < b.size(); ++i)
        fb[i] = b[i];
    ntt(n, 1, fa);
    ntt(n, 1, fb);
    for (int i = 0; i < n; ++i)
        fa[i] = fa[i] * fb[i] % MOD;
    ntt(n, -1, fa);
    return fa;
}

int main() {
    int op;
    scanf("%d", &op);
    if (op == 1) {
        int n, q;
        scanf("%d%d", &n, &q);
        vector<ll> g(n + 1), h(n + 1);
        for (int i = 0; i < n; ++i)
            g[i] = 1;
        for (int i = 0; i <= n; ++i)
            h[i] = 1;
        vector<ll> f = multiply(g, h);
        for (int i = 0; i < q; ++i) {
            int m;
            scanf("%d", &m);
            printf("%lld\n", f[n]);
        }
    } else {
        int q;
        scanf("%d", &q);
        for (int i = 0; i < q; ++i) {
            int n, m;
            scanf("%d%d", &n, &m);
            vector<ll> g(n + 1), h(n + 1);
            for (int k = 0; k <= n; ++k) {
                if (k < m)
                    g[k] = 1;
                else
                    g[k] = 0;
            }
            for (int k = 0; k <= n; ++k) {
                if (k < m)
                    h[k] = 0;
                else
                    h[k] = mod_pow(k - m, MOD - 2) * mod_inv(mod_fact(k - m)) % MOD;
            }
            vector<ll> f = multiply(g, h);
            printf("%lld\n", f[n]);
        }
    }
    return 0;
}