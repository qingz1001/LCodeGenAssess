#include <stdio.h>

typedef long long ll;

int main(){
    ll n, k;
    scanf("%lld %lld", &n, &k);
    
    ll left = 1, right = n, ans = 1;
    while(left <= right){
        ll mid = left + (right - left) / 2;
        if(n / mid >= k){
            ans = mid;
            left = mid + 1;
        }
        else{
            right = mid -1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}