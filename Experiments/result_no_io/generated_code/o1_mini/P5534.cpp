#include <stdio.h>

typedef long long ll;

int main(){
    ll a1, a2, n;
    scanf("%lld %lld %lld", &a1, &a2, &n);
    ll d = a2 - a1;
    ll an = a1 + (n-1)*d;
    ll sum = n * (a1 + an) / 2;
    printf("%lld\n", sum);
    return 0;
}