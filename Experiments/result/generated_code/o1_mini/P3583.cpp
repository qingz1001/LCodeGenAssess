#include <stdio.h>
#include <stdint.h>

typedef long long ll;

int main(){
    ll n;
    scanf("%lld", &n);
    
    ll l =1, r= 1000000000;
    ll res = -1;
    while(l <= r){
        ll m = l + (r - l)/2;
        ll rem = n;
        for(ll i =m; i>=1; i--){
            ll sq = i * i;
            if(sq <= rem){
                rem -= sq;
                if(rem ==0) break;
            }
        }
        if(rem ==0){
            res =m;
            r =m -1;
        }
        else{
            l =m +1;
        }
    }
    if(res==-1){
        printf("- %lld\n", n);
    }
    else{
        ll count = res * res -1;
        printf("%lld %lld\n", res, count);
    }
}