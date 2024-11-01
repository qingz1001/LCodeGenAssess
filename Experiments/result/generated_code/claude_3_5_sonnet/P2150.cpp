#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MOD 1000000007

int n, p;
int prime[MAXN], cnt;
int is_prime[MAXN];
int f[MAXN], g[MAXN];

void sieve() {
    memset(is_prime, 1, sizeof(is_prime));
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            prime[cnt++] = i;
            for (int j = i * 2; j <= n; j += i) {
                is_prime[j] = 0;
            }
        }
    }
}

int fast_pow(int base, int exp) {
    int res = 1;
    while (exp) {
        if (exp & 1) res = (long long)res * base % p;
        base = (long long)base * base % p;
        exp >>= 1;
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &p);
    
    sieve();
    
    f[0] = g[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = g[i] = 1;
        for (int j = 0; j < cnt && prime[j] <= i; j++) {
            if (i % prime[j] == 0) {
                int e = 0;
                while (i % prime[j] == 0) {
                    i /= prime[j];
                    e++;
                }
                f[i] = (long long)f[i] * (e + 1) % (p - 1);
                g[i] = (long long)g[i] * (fast_pow(prime[j], e + 1) - 1) % p * fast_pow(prime[j] - 1, p - 2) % p;
            }
        }
        f[i] = (long long)f[i - 1] * f[i] % (p - 1);
        g[i] = (long long)g[i - 1] * g[i] % p;
    }
    
    int ans = (long long)g[n] * fast_pow(2, f[n]) % p;
    printf("%d\n", ans);
    
    return 0;
}