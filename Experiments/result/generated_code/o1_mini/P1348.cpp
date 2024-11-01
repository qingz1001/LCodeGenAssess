#include <stdio.h>

typedef long long ll;

ll floor_div(ll a, ll k){
    if (k == 0) return 0;
    if (a >= 0) return a / k;
    else{
        if (a % k == 0)
            return a / k;
        else
            return a / k - 1;
    }
}

ll count_divisible(ll a, ll b, ll k){
    return floor_div(b, k) - floor_div(a - 1, k);
}

int main(){
    ll a, b;
    scanf("%lld %lld", &a, &b);
    ll count_odds = floor_div(b + 1, 2) - floor_div(a, 2);
    ll count_mult4 = count_divisible(a, b, 4);
    printf("%lld\n", count_odds + count_mult4);
    return 0;
}