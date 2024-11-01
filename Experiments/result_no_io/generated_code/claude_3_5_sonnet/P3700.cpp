#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 4000001

typedef long long ll;

ll table[MAXN];
int n;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

void update(int a, int b, ll x) {
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    
    ll g = gcd(a, b);
    ll lcm = (ll)a / g * b;
    
    for (int i = 1; i <= n; i++) {
        if (i % (a / g) == 0) {
            int j = b / g * i;
            if (j <= n) {
                ll y = x * lcm / a / b;
                table[i * n + j] = table[j * n + i] = y;
            }
        }
    }
}

ll query(int k) {
    ll sum = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            sum = (sum + table[i * n + j]) % MOD;
        }
    }
    return sum;
}

int main() {
    int m;
    scanf("%d %d", &m, &n);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            table[i * n + j] = (ll)i * j;
        }
    }
    
    while (m--) {
        int a, b, k;
        ll x;
        scanf("%d %d %lld %d", &a, &b, &x, &k);
        update(a, b, x);
        printf("%lld\n", query(k));
    }
    
    return 0;
}