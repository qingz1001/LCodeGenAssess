#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MOD 998244353
#define MAX 400005

typedef long long ll;

// Fast exponentiation
ll powmod_func(ll a, ll b){
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll factorial[MAX];
ll inv_factorial_arr[MAX];

// Precompute factorial and inverse factorial
void precompute(){
    factorial[0] = 1;
    for(int i=1;i < MAX;i++) factorial[i] = factorial[i-1] * i % MOD;
    inv_factorial_arr[MAX-1] = powmod_func(factorial[MAX-1], MOD-2);
    for(int i=MAX-2;i>=0;i--) inv_factorial_arr[i] = inv_factorial_arr[i+1] * (i+1) % MOD;
}

int main(){
    precompute();
    int op;
    scanf("%d", &op);
    if(op ==1 ){
        int n, q;
        scanf("%d %d", &n, &q);
        while(q--){
            int m;
            scanf("%d", &m);
            ll res = 0;
            for(int k=1; k<m; k++){
                res = (res + powmod_func(k, n))%MOD;
            }
            printf("%lld\n", res);
        }
    }
    else if(op ==2 || op ==3 ){
        int q;
        scanf("%d", &q);
        while(q--){
            int n, m;
            scanf("%d %d", &n, &m);
            ll res = 0;
            // To handle large n, limit k
            for(int k=0; k <=n; k++){
                if(n -k < m){
                    continue;
                }
                int p = n -k -m;
                if(p <0) continue;
                ll sign = (p%2 ==0)? 1 : MOD-1;
                if(k + m +1 >= MAX || p >= MAX) continue;
                ll term = powmod_func(k, n);
                term = term * inv_factorial_arr[k + m +1] % MOD;
                term = term * inv_factorial_arr[p] % MOD;
                if(sign == MOD-1){
                    term = MOD - term;
                }
                res = (res + term) % MOD;
            }
            printf("%lld\n", res);
        }
    }
    else if(op ==4 ){
        int q;
        scanf("%d", &q);
        while(q--){
            int n, m;
            scanf("%d %d", &n, &m);
            ll res = 0;
            for(int k=0; k <=n; k++){
                int p = n -k;
                if(p <0) continue;
                ll sign = (p%2 ==0)? 1 : MOD-1;
                if(k >= MAX || p >= MAX) continue;
                ll term = powmod_func(k, n + m);
                term = term * inv_factorial_arr[k] % MOD;
                term = term * inv_factorial_arr[p] % MOD;
                term = term * sign % MOD;
                res = (res + term) % MOD;
            }
            printf("%lld\n", res);
        }
    }
    else if(op ==5 ){
        int q;
        scanf("%d", &q);
        while(q--){
            int n, m;
            scanf("%d %d", &n, &m);
            ll res = 0;
            for(int k=0; k <=m; k++){
                int x = k +1;
                if(x >= MAX) continue;
                ll term1 = powmod_func(x, n + m +1);
                if(x >= MAX) continue;
                term1 = term1 * inv_factorial_arr[x] % MOD;
                ll sum_inner = 0;
                for(int i=0; i <= m -k; i++){
                    if(2*n +1 < i) continue;
                    // Compute binom(2n+1, i)
                    if(2*n+1 >= MAX || i >= MAX || (m -k -i) <0) continue;
                    ll binom = factorial[2*n +1] * inv_factorial_arr[i] % MOD;
                    binom = binom * inv_factorial_arr[2*n +1 -i] % MOD;
                    // (-1)^{m -k}
                    ll sign = ((m -k)%2 ==0)? 1 : MOD-1;
                    // (m -k -i)! inverse
                    ll inv_fact = (m -k -i)>=0 ? inv_factorial_arr[m -k -i] : 0;
                    // x^{-i} = pow(x, MOD-2)^i
                    ll inv_x = powmod_func(x, MOD-2);
                    ll inv_x_i = 1;
                    if(i >0){
                        ll base = inv_x;
                        int exp = i;
                        while(exp >0){
                            if(exp &1){
                                inv_x_i = inv_x_i * base % MOD;
                            }
                            base = base * base % MOD;
                            exp >>=1;
                        }
                    }
                    ll inner = binom * sign % MOD;
                    inner = inner * inv_fact % MOD;
                    inner = inner * inv_x_i % MOD;
                    sum_inner = (sum_inner + inner) % MOD;
                }
                term1 = term1 * sum_inner % MOD;
                res = (res + term1) % MOD;
            }
            printf("%lld\n", res);
        }
    }
    return 0;
}