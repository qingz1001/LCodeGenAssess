#include <stdio.h>

typedef long long ll;

ll fast_pow(ll a, ll b, ll p){
    ll res = 1;
    a %= p;
    while(b > 0){
        if(b & 1){
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main(){
    ll a, b, p;
    scanf("%lld %lld %lld", &a, &b, &p);
    ll s = fast_pow(a, b, p);
    printf("%lld^%lld mod %lld=%lld\n", a, b, p, s);
    return 0;
}