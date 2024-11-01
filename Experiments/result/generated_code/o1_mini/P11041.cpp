#include <stdio.h>

typedef long long ll;

ll count(ll x){
    return x / 20 + x / 24 - x / 120;
}

int main(){
    ll n = 202420242024;
    ll low = 1, high = n * 24;
    while(low < high){
        ll mid = low + (high - low) / 2;
        if(count(mid) < n){
            low = mid + 1;
        }
        else{
            high = mid;
        }
    }
    printf("%lld", low);
    return 0;
}