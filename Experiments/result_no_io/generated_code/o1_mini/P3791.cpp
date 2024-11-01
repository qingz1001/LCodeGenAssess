#include <stdio.h>
#include <math.h>

typedef long long ll;

const int MOD = 998244353;

// Function to compute number of divisors of z
int count_divisors(ll z){
    if(z == 0) return 0;
    int cnt = 0;
    ll sqrt_z = sqrt((double)z);
    for(ll d = 1; d <= sqrt_z; d++){
        if(z % d == 0){
            cnt += 2;
            if(d * d == z) cnt--;
        }
    }
    return cnt;
}

int main(){
    ll n, m, x;
    scanf("%lld %lld %lld", &n, &m, &x);
    ll total = 0;
    for(ll i = 0; i <= n; i++){
        for(ll j = 0; j <= m; j++){
            ll z = (i ^ j) ^ x;
            if(z == 0) continue;
            total = (total + count_divisors(z)) % MOD;
        }
    }
    printf("%lld\n", total);
    return 0;
}