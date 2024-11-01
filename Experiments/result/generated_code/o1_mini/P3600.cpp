#include <stdio.h>
#include <stdbool.h>

typedef long long ll;

const int MOD = 666623333;

// Function to perform modular exponentiation
ll pow_mod_func(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>=1;
    }
    return res;
}

int main(){
    int n, x, q;
    scanf("%d %d %d", &n, &x, &q);
    bool covered[2001] = {false};
    for(int i=0;i<q;i++){
        int l, r;
        scanf("%d %d", &l, &r);
        for(int j=l; j<=r; j++) covered[j] = true;
    }
    int m=0;
    for(int j=1; j<=n; j++) if(covered[j]) m++;
    ll inv_x = pow_mod_func(x, MOD-2, MOD);
    ll ans=0;
    for(int k=1; k<=x; k++){
        ll s = ((x - k +1) * inv_x) % MOD;
        ll s_p = pow_mod_func(s, m, MOD);
        ll tmp = (1 + MOD - s_p) % MOD;
        ans = (ans + tmp) % MOD;
    }
    printf("%lld\n", ans);
}