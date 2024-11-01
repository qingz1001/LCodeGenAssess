#include <stdio.h>
#define MOD 998244353
typedef long long ll;

// Fast exponentiation
ll power_mod(ll a, ll b){
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1){
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>=1;
    }
    return res;
}

ll dp_max = 200005;
ll dp[200005];

int main(){
    int n, m, l;
    scanf("%d %d %d", &n, &m, &l);
    // Read S, but not used
    for(int i=0;i<l;i++) {
        int tmp;
        scanf("%d", &tmp);
    }
    dp[0] =1;
    for(int i=1;i<=n;i++){
        dp[i] = (dp[i-1] * m) % MOD;
        if(i >= l){
            dp[i] = (dp[i] - dp[i - l] + MOD) % MOD;
        }
    }
    ll A = dp[n];
    ll total = power_mod(m, n);
    ll inv_total = power_mod(total, MOD -2);
    ll prob = ((total - A + MOD) % MOD) * inv_total % MOD;
    printf("%lld\n", prob);
}