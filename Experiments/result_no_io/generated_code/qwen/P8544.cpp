#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef long long ll;

int main() {
    int n, m, t;
    scanf("%d %d %d", &n, &m, &t);
    
    ll *a = (ll *)malloc(n * sizeof(ll));
    ll *b = (ll *)malloc(m * sizeof(ll));
    
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }
    
    for (int i = 0; i < m; ++i) {
        scanf("%lld", &b[i]);
    }
    
    ll ans = 0;
    
    for (int j = 0; j < t; ++j) {
        ll sum = 0;
        for (int i = 0; i < n; ++i) {
            if (j % 2 == 0) {
                sum += a[i] * (b[j / 2] + 1);
            } else {
                sum += a[i] * b[j / 2];
            }
            sum %= MOD;
        }
        ans += sum;
        ans %= MOD;
    }
    
    printf("%lld\n", ans);
    
    free(a);
    free(b);
    
    return 0;
}