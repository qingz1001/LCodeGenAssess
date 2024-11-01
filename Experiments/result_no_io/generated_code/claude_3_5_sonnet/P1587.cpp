#include <stdio.h>
#include <string.h>

#define MAX 2000005

int n, m, k;
int prime[MAX], cnt;
int mindiv[MAX];
int mu[MAX];

void sieve(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!mindiv[i]) {
            prime[cnt++] = i;
            mindiv[i] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < cnt && prime[j] * i <= n; j++) {
            int p = prime[j];
            mindiv[i * p] = p;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int phi(int x) {
    int res = x;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) res = res / x * (x - 1);
    return res;
}

long long solve(int n, int m) {
    long long ans = 0;
    for (int i = 1; i <= n && i <= m; i++) {
        ans += (long long)phi(i) * (n / i) * (m / i);
    }
    return ans;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    if (n > m) {
        int temp = n;
        n = m;
        m = temp;
    }
    
    sieve(n);
    
    long long ans = 0;
    for (int d = 1; d <= n; d++) {
        int l = lcm(d, k);
        ans += mu[d] * solve(n / d, m / d);
    }
    
    printf("%lld\n", ans);
    return 0;
}