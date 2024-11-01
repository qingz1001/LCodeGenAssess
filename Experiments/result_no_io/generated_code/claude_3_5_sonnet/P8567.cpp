#include <stdio.h>

typedef long long ll;

ll count_pairs(ll l, ll r) {
    ll count = 0;
    ll mask = 1;
    
    while (mask <= r) {
        ll left = (l + mask - 1) / mask * mask;
        ll right = r / mask * mask;
        
        if (left <= right) {
            count += (right - left) / (mask * 2);
        }
        
        mask *= 2;
    }
    
    return count;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        ll l, r;
        scanf("%lld %lld", &l, &r);
        printf("%lld\n", count_pairs(l, r));
    }
    
    return 0;
}