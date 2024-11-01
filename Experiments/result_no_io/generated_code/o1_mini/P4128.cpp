#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

ll power_mod(ll a, ll b, ll mod){
    ll res=1;a %= mod;
    while(b>0){
        if(b&1) res = res * a % mod;
        a = a * a % mod;
        b >>=1;
    }
    return res;
}

int main(){
    int n, m;
    ll p;
    scanf("%d %d %lld", &n, &m, &p);
    
    // Compute factorial and inverse factorial
    ll fact[54];
    fact[0]=1;
    for(int i=1;i<=n;i++) fact[i]=(fact[i-1]*i)%p;
    
    ll inv_fact[54];
    inv_fact[n] = power_mod(fact[n], p-2, p);
    for(int i=n-1;i>=0;i--) inv_fact[i]=(inv_fact[i+1]*(i+1))%p;
    
    // Precompute floor(l/2)
    int floor_half[54];
    for(int l=0;l<=n;l++) floor_half[l]=l/2;
    
    // Initialize DP
    // dp[i][k][s]
    // i: current number of elements
    // k: number of cycles
    // s: sum of floor(l/2)
    // To save space, use two layers
    int max_s = (n/2)*n;
    ll **dp_prev = (ll **)calloc((n+1)*(n+1), sizeof(ll));
    ll **dp_curr = (ll **)calloc((n+1)*(n+1), sizeof(ll));
    memset(dp_prev, 0, sizeof(ll)*(n+1)*(n+1));
    // Initialize dp[0][0][0] =1
    dp_prev[0*(n+1)+0] =1;
    
    for(int l=1;l<=n;l++){
        // Not used in this approach
    }
    
    // Implement DP
    // To handle s, use separate array
    ll dp[54][54][1381];
    memset(dp, 0, sizeof(dp));
    dp[0][0][0]=1;
    for(int i=0;i<n;i++){
        for(int k=0;k<=i;k++){
            for(int s=0;s<= (i)*26;s++){
                if(dp[i][k][s]==0) continue;
                for(int l=1;l<=n-i;l++){
                    int ni = i + l;
                    int nk = k +1;
                    int ns = s + floor_half[l];
                    if(ns > 1380) continue;
                    // Compute C(n-i, l)
                    // C(n-i,l) = fact[n-i] / (fact[l]*fact[n-i-l])
                    if(n-i < l) continue;
                    ll comb = (fact[n-i] * inv_fact[l]) % p;
                    comb = (comb * inv_fact[n-i-l]) % p;
                    // Multiply by (l-1)! 
                    ll ways = (comb * fact[l-1]) % p;
                    dp[ni][nk][ns] = (dp[ni][nk][ns] + dp[i][k][s] * ways % p) % p;
                }
            }
        }
    }
    
    // Precompute powers of m
    // Maximum c(k,s) = C(k,2) + s
    // C(53,2) + 26*53 = 1378 + 53*52/2=1378 + 1378=2756
    // But to be safe, compute up to 3000
    ll pow_m[3001];
    pow_m[0]=1%p;
    for(int i=1;i<=3000;i++) pow_m[i]=(pow_m[i-1]*m)%p;
    
    // Compute sum
    ll total =0;
    for(int k=0;k<=n;k++){
        for(int s=0;s<= (n/2)*n;s++){
            if(dp[n][k][s]==0) continue;
            ll c = ((ll)k * (k-1) /2) + s;
            if(c > 3000) continue;
            total = (total + dp[n][k][s] * pow_m[c] % p) % p;
        }
    }
    
    // Compute inverse of fact[n]
    ll inv_n_fact = power_mod(fact[n], p-2, p);
    total = (total * inv_n_fact) % p;
    printf("%lld\n", total);
    
    return 0;
}