#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353
#define MAX 100005

typedef long long ll;

// Fast exponentiation
ll power_ll(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>=1;
    }
    return res;
}

ll inv_fact[MAX];
ll fact[MAX];
ll f[MAX];
ll prefix_f[MAX];

// Precompute factorial and inverse factorial
void precompute(){
    fact[0] = 1;
    for(int i=1;i<MAX;i++) fact[i] = fact[i-1]*i % MOD;
    inv_fact[MAX-1] = power_ll(fact[MAX-1], MOD-2);
    for(int i=MAX-2;i>=0;i--) inv_fact[i] = inv_fact[i+1]*(i+1) % MOD;
}

// Main function to compute f(n)
int main(){
    int n;
    scanf("%d", &n);
    precompute();
    f[0] = 1;
    prefix_f[0] = 1;
    for(int i=1;i<=n;i++){
        ll sum = 0;
        for(int k=0;k<=i;k++){
            sum = (sum + f[k] * power_ll(k, i - k) % MOD * inv_fact[i - k]) % MOD;
        }
        f[i] = sum * power_ll(3, MOD-2) % MOD;
        prefix_f[i] = (prefix_f[i-1] + f[i]) % MOD;
    }
    printf("%lld\n", prefix_f[n]);
    return 0;
}