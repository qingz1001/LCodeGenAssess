#include <stdio.h>
#include <stdint.h>

#define MOD 19940417

typedef long long ll;

// Function to compute sum of (x mod i) from i=1 to x
ll sum_mod(ll x) {
    ll res = 0;
    for(ll i=1, j; i <= x; i = j + 1){
        ll q = x / i;
        j = x / q;
        if(j > x) j = x;
        res += q * (j - i + 1) * i - (j*(j+1)/2 - (i-1)*i/2);
    }
    return res;
}

// Function to compute sum of (x mod i)*(y mod i) from i=1 to k
ll sum_mod_mul(ll x, ll y, ll k) {
    ll res = 0;
    for(ll i=1, j; i <= k; i = j + 1){
        ll qx = x / i;
        ll qy = y / i;
        j = x / qx;
        if(j > y / qy) j = y / qy;
        if(j > k) j = k;
        ll cnt = j - i + 1;
        ll sum_x = qx * (j - i + 1) * i - (j*(j+1)/2 - (i-1)*i/2);
        ll sum_y = qy * (j - i + 1) * i - (j*(j+1)/2 - (i-1)*i/2);
        res += (sum_x % MOD) * (sum_y % MOD) % MOD;
        res %= MOD;
    }
    return res;
}

int main(){
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll sum_n = sum_mod(n) % MOD;
    ll sum_m = sum_mod(m) % MOD;
    ll total = (sum_n * sum_m) % MOD;
    ll k = n < m ? n : m;
    ll sum_k = sum_mod_mul(n, m, k) % MOD;
    ll answer = (total - sum_k + MOD) % MOD;
    printf("%lld\n", answer);
    return 0;
}