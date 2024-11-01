#include <stdio.h>
#include <math.h>

typedef long long ll;

ll count_ways(ll m) {
    ll count = 0;
    for (ll k = 2; k * k <= m; ++k) {
        ll sum = 1;
        ll term = 1;
        for (int i = 1; i <= 4; ++i) {
            term *= k;
            sum += term;
        }
        count += m / sum;
    }
    return count;
}

ll find_min_m(ll n) {
    ll low = 1, high = 1e18;
    ll result = -1;
    while (low <= high) {
        ll mid = (low + high) / 2;
        if (count_ways(mid) >= n) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return result;
}

int main() {
    ll n;
    scanf("%lld", &n);
    printf("%lld\n", find_min_m(n));
    return 0;
}