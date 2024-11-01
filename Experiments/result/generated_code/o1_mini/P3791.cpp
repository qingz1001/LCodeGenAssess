#include <stdio.h>
#include <stdlib.h>
#define MOD 998244353

typedef long long ll;

int main(){
    ll n, m, x;
    scanf("%lld %lld %lld", &n, &m, &x);
    ll max_y = n > m ? n : m;
    max_y = max_y * 2 + x;
    ll limit = max_y < (1<<20) ? (1<<20) : max_y;
    ll *d = calloc(limit+1, sizeof(ll));
    for(ll i=1;i<=limit;i++) {
        for(ll j=i; j<=limit; j+=i){
            d[j]++;
        }
    }
    ll result = 0;
    for(ll y=0; y<=limit; y++){
        ll k = y ^ x;
        if(k == 0 || k > limit) continue;
        ll count;
        ll m_xor_y = m ^ y;
        if(m_xor_y > n){
            count = n + 1;
        }
        else{
            count = m_xor_y + 1;
        }
        if(count < 0) count = 0;
        if(k <= limit){
            result = (result + (d[k] * count) % MOD) % MOD;
        }
    }
    printf("%lld\n", result);
    free(d);
    return 0;
}