#include <stdio.h>
#include <stdint.h>

typedef long long ll;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    ll a;
    ll max_a = -__INT64_MAX__;
    ll min_a = __INT64_MAX__;
    for(int i=0;i<n;i++){
        scanf("%lld", &a);
        if(a > max_a) max_a = a;
        if(a < min_a) min_a = a;
    }
    ll power2[11];
    power2[0] = 1;
    for(int i=1;i<=10;i++) power2[i] = power2[i-1] * 2;
    ll result = -__INT64_MAX__;
    for(int k=0;k<=m;k++){
        if(k > 10) continue; // since m <=10
        if(m -k >10) continue;
        ll current_max = max_a * power2[k];
        ll current_min = min_a - 2LL*(m -k);
        ll range = current_max - current_min;
        if(range > result) result = range;
    }
    printf("%lld\n", result);
    return 0;
}