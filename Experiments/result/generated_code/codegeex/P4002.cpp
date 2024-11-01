#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#define int long long
using namespace std;
const int maxn = 3e4 + 10;
const int mod = 998244353;
int n, m, a[maxn], s[maxn], fac[maxn], inv[maxn], sum[maxn], c[maxn], ans, invfac[maxn];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int C(int n, int m) {
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), s[i] = (s[i - 1] + a[i]) % mod;
    
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = qpow(fac[n], mod - 2);
    for (int i = n; i >= 1; i--) invfac[i - 1] = invfac[i] * i % mod;
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            c[j] = (c[j] + invfac[j / i - 1]) % mod;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        sum[i] = (sum[i - 1] + c[i]) % mod;
    }
    
    for (int i = 1; i <= n; i++) {
        int x = qpow(s[i], m);
        int y = qpow(a[i] - s[i], m);
        ans = (ans + x * sum[i - 1] % mod * y) % mod;
    }
    
    printf("%lld\n", ans);
    return 0;
}