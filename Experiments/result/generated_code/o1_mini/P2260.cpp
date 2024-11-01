#include <stdio.h>
#define MOD 19940417

typedef long long ll;

// Function to compute sum of (x mod i) for i from 1 to x
ll sum_mod(ll x) {
    ll res = 0;
    ll i = 1;
    while(i <= x){
        ll q = x / i;
        ll next = x / q;
        if(next > x) next = x;
        res += (q * (next - i +1)) - ((next - i +1) * (next + i)) / 2;
        i = next +1;
    }
    return res;
}

// Function to compute sum of (a mod i) * (b mod i) for i from 1 to k
ll sum_mod_mult(ll a, ll b, ll k){
    ll res = 0;
    ll i =1;
    while(i <= k){
        ll qa = a / i;
        ll qb = b / i;
        ll q = qa < qb ? qa : qb;
        if(q ==0){
            res += (a % i) * (b % i);
            i++;
            continue;
        }
        ll next_a = a / q;
        ll next_b = b / q;
        ll next = next_a < next_b ? next_a : next_b;
        if(next > k) next = k;
        for(ll j=i; j<=next; j++) {
            res += (a % j) * (b % j);
            if(res >= MOD) res %= MOD;
        }
        i = next +1;
    }
    return res % MOD;
}

int main(){
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll sum_n = sum_mod(n);
    ll sum_m = sum_mod(m);
    ll min_nm = n < m ? n : m;
    ll sum_common = sum_mod_mult(n, m, min_nm);
    ll total = (sum_n % MOD) * (sum_m % MOD) % MOD;
    total = (total - sum_common % MOD + MOD) % MOD;
    printf("%lld\n", total);
    return 0;
}