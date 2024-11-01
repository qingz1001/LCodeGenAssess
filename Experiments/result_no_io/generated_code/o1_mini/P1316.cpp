#include <stdio.h>

typedef long long ll;

const int MOD = 1000000007;

// Function to compute a^b mod MOD
ll power_mod(ll a, ll b, ll mod){
    ll result = 1;
    a %= mod;
    while(b > 0){
        if(b & 1){
            result = result * a % mod;
        }
        a = a * a % mod;
        b >>=1;
    }
    return result;
}

int main(){
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll E =0;
    for(ll l=1;l<=n;l++){
        ll k = n - l +1;
        ll A = power_mod(m, l, MOD);
        // Compute B = (A-1)^k mod MOD
        ll B;
        if(A ==0){
            B = power_mod(MOD-1, k, MOD); // (0-1)^k = (-1)^k
        }
        else{
            B = power_mod((A -1 + MOD)%MOD, k, MOD);
        }
        // Compute C = inv(A) mod MOD
        ll C = power_mod(A, MOD-2, MOD);
        // Compute D = C^k mod MOD
        ll D = power_mod(C, k, MOD);
        // Compute tmp = (B * D) mod MOD
        ll tmp = (B * D) % MOD;
        // Compute (1 - tmp) mod MOD
        tmp = (1 - tmp + MOD) % MOD;
        // Compute E_l = (A * tmp) mod MOD
        ll E_l = (A * tmp) % MOD;
        // Add to E
        E = (E + E_l) % MOD;
    }
    printf("%lld\n", E);
}