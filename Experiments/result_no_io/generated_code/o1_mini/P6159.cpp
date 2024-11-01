#include <stdio.h>

typedef long long ll;

int main(){
    ll n, p, k;
    scanf("%lld %lld %lld", &n, &p, &k);
    ll t = (p * (k + 1)) % n;
    printf("%lld\n", t);
    return 0;
}