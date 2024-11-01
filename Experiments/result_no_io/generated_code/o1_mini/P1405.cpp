#include <stdio.h>

typedef long long ll;

ll powmod(ll a, ll e, ll mod){
    ll res = 1;
    a %= mod;
    while(e > 0){
        if(e & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        e >>= 1;
    }
    return res;
}

#define MAXN 1234567
int a[MAXN];

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    ll exponent = 1;
    for(int i = n-1; i >= 0; i--){
        exponent = powmod(a[i], exponent, 10006);
        if(exponent == 0) exponent = 10006;
    }
    ll result = powmod(a[0], exponent, 10007);
    printf("%lld\n", result);
    return 0;
}