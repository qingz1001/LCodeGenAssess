#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    ll k, m, n;
    if(scanf("%lld %lld %lld", &k, &m, &n)!=3){
        return 1;
    }
    // Allocate space for indices, max m=30000
    ll *ans = (ll*)malloc(sizeof(ll)*m);
    if(!ans){
        return 1;
    }
    ll count=0;
    for(ll i=1;i<=m;i++){
        ll a, b;
        if(scanf("%lld %lld", &a, &b)!=2){
            free(ans);
            return 1;
        }
        if(a == 0){
            if(b >= n){
                ans[count++] = i;
            }
        }
        else{
            ll t = k / a;
            if(t >=1){
                // To prevent overflow, use 64-bit
                __int128 damage = (__int128)t * b;
                if(damage >= n){
                    ans[count++] = i;
                }
            }
        }
    }
    if(count >0){
        for(ll i=0;i<count;i++){
            if(i>0){
                printf(" ");
            }
            printf("%lld", ans[i]);
        }
        printf("\n");
    }
    else{
        printf("-1\n");
    }
    free(ans);
    return 0;
}