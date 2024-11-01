#include <stdio.h>
#include <stdint.h>

typedef unsigned long long ull;

ull powmod_func(ull base, ull exp, ull mod) {
    ull res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            res = (__int128(res) * base) % mod;
        base = (__int128(base) * base) % mod;
        exp >>= 1;
    }
    return res;
}

int main(){
    int T;
    if(scanf("%d", &T)!=1)return 0;
    while(T--){
        ull n, k, p;
        if(scanf("%llu %llu %llu", &n, &k, &p)!=3)return 0;
        ull ans;
        if(n & 1){
            ans = powmod_func(k, n, p);
        }
        else{
            ull half = powmod_func(k, n/2, p);
            ans = ( (__int128(2) * half) % p + p - (k % p)) % p;
        }
        printf("%llu\n", ans);
    }
    return 0;
}