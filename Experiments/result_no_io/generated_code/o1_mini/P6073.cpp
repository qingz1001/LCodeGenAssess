#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MOD 998244353
typedef long long ll;

// Fast exponentiation
ll power_mod(ll a, ll b){
    ll res=1;a%=MOD;
    while(b>0){
        if(b&1) res=res*a%MOD;
        a=a*a%MOD; b >>=1;
    }
    return res;
}

// Modular inverse using Fermat
ll inv_mod(ll a){
    return power_mod(a, MOD-2);
}

// Precompute factorial and inverse factorial
ll fact[4000005];
ll inv_fact[4000005];

void precompute_fact(int max_n){
    fact[0]=1;
    for(int i=1;i<=max_n;i++) fact[i]=fact[i-1]*i%MOD;
    inv_fact[max_n]=inv_mod(fact[max_n]);
    for(int i=max_n-1;i>=0;i--) inv_fact[i]=inv_fact[i+1]*(i+1)%MOD;
}

int main(){
    int op;
    scanf("%d", &op);
    if(op == 1){
        int n, q;
        scanf("%d %d", &n, &q);
        // Compute k^n for k from 0 to n
        ll *powk = (ll*)calloc(n+1, sizeof(ll));
        powk[0] = 0;
        if(n >0) powk[1] = 1;
        for(int k=2; k<=n; k++) powk[k] = power_mod(k, n);
        // Compute prefix sums
        ll *prefix = (ll*)calloc(n+2, sizeof(ll));
        prefix[0] = 0;
        for(int k=1; k<=n; k++) prefix[k] = (prefix[k-1] + powk[k])%MOD;
        while(q--){
            int m;
            scanf("%d", &m);
            if(m-1 >= n) m = n+1;
            if(m-1 <0) m=0;
            else m = m-1;
            printf("%lld\n", prefix[m]);
        }
        free(powk);
        free(prefix);
    }
    else{
        int q;
        scanf("%d", &q);
        // Precompute factorials up to 4e5 for subtask 2,3,4,5
        precompute_fact(4000000);
        while(q--){
            ll n, m;
            scanf("%lld %lld", &n, &m);
            if(op ==2 || op==3){
                // f_n = sum_{k=0}^n (k^n * g_k * h_{n-k})
                // g_k = 1 / (k + m +1)!
                // h_k = 0 if k <m else (-1)^{k-m} / (k-m)!
                // f_n = sum_{k=m}^n k^n / (k+m+1)! * (-1)^{k-m} / (n-k -m)!)
                // This seems similar to coefficient extraction, but likely precompute
                // However m <=20, n<=2e5 or 998244352
                // It might relate to some combinatorial identity
                // Alternatively, implement directly for small m
                ll res=0;
                for(ll k=0; k<=n; k++){
                    // g_k = inv_fact[k + m +1]
                    ll gk = inv_fact[k + m +1];
                    // h_{n-k} = 0 if n-k <m else (-1)^{n-k -m} * inv_fact[n-k -m]
                    if(n -k < m) continue;
                    ll sign = ((n -k -m) &1) ? MOD -1 : 1;
                    ll hk = sign * inv_fact[n -k -m] % MOD;
                    // k^n
                    ll kn;
                    if(k ==0 && n >0){kn=0;}
                    else{kn = power_mod(k, n);}
                    res = (res + kn * gk % MOD * hk % MOD)%MOD;
                }
                printf("%lld\n", res);
            }
            else if(op ==4){
                // g_k = k^m /k!
                // h_k = (-1)^k /k!
                // f_n = sum_{k=0}^n k^m /k! * (-1)^{n -k} / (n -k)!}
                // Which is sum_{k=0}^n k^m * (-1)^{n -k} * inv_fact[k] * inv_fact[n -k]
                ll res=0;
                for(ll k=0; k<=n; k++){
                    if(k > m) continue;
                    ll sign = ((n -k) &1) ? MOD -1 : 1;
                    ll term = power_mod(k, m) * sign % MOD;
                    term = term * inv_fact[k] % MOD;
                    term = term * inv_fact[n -k] % MOD;
                    res = (res + term) % MOD;
                }
                printf("%lld\n", res);
            }
            else if(op ==5){
                // sum_{k=0}^m (k+1)^m * (k+1)^{n+1} / (k+1)! * sum_{i=0}^{m -k} binom(2n+1,i) * (-1)^{m -k} / (m -k -i)! / (k+1)^i
                // Simplify: sum_{k=1}^{m+1} k^m * k^{n+1} /k! * sum_{i=0}^{m -k+1} C(2n+1,i) * (-1)^{m -k+1} / (m -k+1 -i)! /k^i
                // Change variable to k =k'+1
                ll res=0;
                for(ll k=0; k<=m; k++){
                    ll term1 = power_mod(k+1, m + n +1);
                    term1 = term1 * inv_fact[k+1] % MOD;
                    ll inner =0;
                    for(ll i=0; i<=m -k; i++){
                        if(2*n+1 < i) continue;
                        ll binom = fact[2*n+1] * inv_fact[i] % MOD * inv_fact[2*n+1 -i] % MOD;
                        ll sign = ((m -k) &1) ? MOD -1 : 1;
                        if((m -k -i) <0) continue;
                        ll denominator = inv_fact[m -k -i];
                        ll ki = power_mod(k+1, i);
                        ll tmp = binom * sign % MOD;
                        tmp = tmp * denominator % MOD;
                        tmp = tmp * power_mod(k+1, MOD-2) % MOD;
                        inner = (inner + tmp) % MOD;
                    }
                    term1 = term1 * inner % MOD;
                    res = (res + term1) % MOD;
                }
                printf("%lld\n", res);
            }
        }
    }
    return 0;
}