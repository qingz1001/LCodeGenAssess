#include <stdio.h>

typedef long long ll;

int main(){
    ll n, k;
    while(scanf("%lld %lld", &n, &k)!=EOF){
        if(k<=1){
            printf("%lld\n", n);
            continue;
        }
        ll total = n;
        ll butts = n;
        while(butts >=k){
            ll new_cigs = butts /k;
            total += new_cigs;
            butts = butts %k + new_cigs;
        }
        printf("%lld\n", total);
    }
    return 0;
}