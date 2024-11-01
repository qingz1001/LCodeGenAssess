#include <stdio.h>
#include <string.h>

#define MAX_M 10001
#define MAX_A 100000001

typedef long long ll;

ll M, P, A, O, S, U;
ll dp[MAX_M][5];
ll pow_mod[MAX_A];
ll inv_mod[MAX_M];

ll quick_pow(ll x, ll n, ll mod) {
    ll res = 1;
    while (n) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

void init() {
    pow_mod[0] = 1;
    for (int i = 1; i < MAX_A; i++) {
        pow_mod[i] = pow_mod[i-1] * U % P;
    }
    
    inv_mod[1] = 1;
    for (int i = 2; i <= M; i++) {
        inv_mod[i] = (P - P / i) * inv_mod[P % i] % P;
    }
}

int main() {
    scanf("%lld%lld", &M, &P);
    scanf("%lld%lld%lld%lld", &A, &O, &S, &U);
    
    init();
    
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k <= i; k++) {
                ll tmp = (O * k * k + S * k + U) % P;
                ll contrib = dp[i-k][j] * tmp % P;
                dp[i][(j+1)%5] = (dp[i][(j+1)%5] + contrib) % P;
            }
        }
    }
    
    ll ans = 0;
    for (int i = 1; i <= M; i++) {
        ll sum = 0;
        for (int j = 0; j < 5; j++) {
            sum = (sum + dp[i][j]) % P;
        }
        ll tmp = sum * pow_mod[A-i] % P;
        ans = (ans + tmp * inv_mod[i]) % P;
    }
    
    printf("%lld\n", ans);
    
    return 0;
}