#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MOD 1000000007
#define MAX 2000001

ll fact[MAX];
ll inv_fact_arr[MAX];

// Fast exponentiation
ll power(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    ll sum_C = 0;
    for(int i =0;i<M;i++){
        int Ci;
        scanf("%d", &Ci);
        sum_C += Ci;
    }
    ll x = N - sum_C - M;
    
    // Precompute factorial
    fact[0] = 1;
    for(int i=1;i<MAX;i++) fact[i] = fact[i-1] * i % MOD;
    
    // Precompute inverse factorial
    inv_fact_arr[MAX-1] = power(fact[MAX-1], MOD-2);
    for(int i=MAX-2;i>=0;i--) inv_fact_arr[i] = inv_fact_arr[i+1] * (i+1) % MOD;
    
    // Compute C(x + M -1, M -1)
    ll a = x + M -1;
    ll b = M -1;
    if(a < b){
        printf("0\n");
        return 0;
    }
    ll comb = fact[a] * inv_fact_arr[b] % MOD;
    comb = comb * inv_fact_arr[a - b] % MOD;
    printf("%lld\n", comb);
    return 0;
}