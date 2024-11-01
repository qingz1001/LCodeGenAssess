#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_C 100000
#define MAX_N 1000000000
#define MAX_M 1000000000

typedef long long ll;

int T, n, m, c;
ll x[MAX_C], y[MAX_C];

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int solve() {
    if (c >= n * m - 1) return -1;
    if (c == 0) return (n > 1 || m > 1) ? 0 : -1;
    if (n == 1 && m == 1) return -1;
    
    ll g = 0;
    for (int i = 0; i < c; i++) {
        g = gcd(g, x[i] * m + y[i]);
    }
    
    if (g == 1) return 1;
    
    ll total = (ll)n * m;
    ll cycle = total / g;
    
    if (cycle == c + 1) return -1;
    return (cycle == c + 2) ? 2 : 1;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &m, &c);
        for (int i = 0; i < c; i++) {
            scanf("%lld %lld", &x[i], &y[i]);
            x[i]--;
            y[i]--;
        }
        printf("%d\n", solve());
    }
    return 0;
}