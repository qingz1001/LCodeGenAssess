#include <stdio.h>
#include <math.h>

typedef long long ll;

ll find_min_x(ll n) {
    if(n == 1) return 1;
    ll left = 1, right = 10000000000LL;
    while(left < right){
        ll mid = left + (right - left) / 2;
        double log_val = mid * log10((double)mid);
        ll digits = (ll)floor(log_val) + 1;
        if(digits >= n){
            right = mid;
        }
        else{
            left = mid +1;
        }
    }
    return left;
}

int main(){
    ll n;
    scanf("%lld", &n);
    printf("%lld\n", find_min_x(n));
    return 0;
}