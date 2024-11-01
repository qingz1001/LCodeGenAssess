#include <stdio.h>
#include <string.h>

#define MAX_M 5
#define MAX_P 100000

typedef long long ll;

ll P, n, m;
ll w[MAX_M + 1];
ll dp[MAX_M + 1][MAX_P + 1];

ll pow_mod(ll base, ll exp) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % P;
        base = base * base % P;
        exp >>= 1;
    }
    return result;
}

ll inv(ll x) {
    return pow_mod(x, P - 2);
}

int main() {
    scanf("%lld", &P);
    scanf("%lld %lld", &n, &m);
    
    ll sum = 0;
    for (int i = 1; i <= m; i++) {
        scanf("%lld", &w[i]);
        sum += w[i];
    }
    
    if (sum > n) {
        printf("Impossible\n");
        return 0;
    }
    
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= w[i] && k <= j; k++) {
                dp[i][j] = (dp[i][j] + dp[i-1][j-k]) % P;
            }
        }
    }
    
    ll result = dp[m][n];
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= w[i]; j++) {
            result = result * inv(j) % P;
        }
    }
    
    printf("%lld\n", result);
    
    return 0;
}