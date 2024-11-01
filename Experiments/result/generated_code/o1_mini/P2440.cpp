#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n;
    ll k;
    scanf("%d %lld", &n, &k);
    
    ll *L = (ll*)malloc(n * sizeof(ll));
    ll max_L = 0;
    for(int i = 0; i < n; i++){
        scanf("%lld", &L[i]);
        if(L[i] > max_L){
            max_L = L[i];
        }
    }
    
    ll left = 1, right = max_L, res = 0;
    while(left <= right){
        ll mid = left + (right - left) / 2;
        ll count = 0;
        for(int i = 0; i < n; i++){
            count += L[i] / mid;
            if(count >= k){
                break;
            }
        }
        if(count >= k){
            res = mid;
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    
    printf("%lld\n", res);
    free(L);
    return 0;
}