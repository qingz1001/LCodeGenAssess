#include <stdio.h>

typedef long long ll;

ll powmod(ll a, ll b, ll p){
    ll res = 1;
    a %= p;
    while(b > 0){
        if(b & 1){
            res = res * a % p;
        }
        a = a * a % p;
        b >>=1;
    }
    return res;
}

int main(){
    ll a, b, p;
    if(scanf("%lld %lld %lld", &a, &b, &p)!=3){
        return 1;
    }
    ll s = powmod(a, b, p);
    printf("%lld^%lld mod %lld=%lld\n", a, b, p, s);
    return 0;
}