#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef long long ll;

ll max(ll a, ll b){
    return a > b ? a : b;
}

int main(){
    int n;
    ll a, b;
    scanf("%d %lld %lld", &n, &a, &b);
    ll *w = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld", &w[i]);
    ll low = 0;
    ll high = 2000000000;
    while(low < high){
        ll mid = low + (high - low) / 2;
        ll S = 0;
        for(int i=0;i<n;i++){
            if(w[i] > a * mid){
                ll required = w[i] - a * mid;
                S += (required + b - 1) / b;
                if(S > mid) break;
            }
        }
        if(S <= mid) high = mid;
        else low = mid + 1;
    }
    printf("%lld\n", low);
    free(w);
    return 0;
}