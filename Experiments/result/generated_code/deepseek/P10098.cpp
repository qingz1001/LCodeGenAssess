#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define MAXP 1000000000000LL

typedef long long ll;

int n;
ll p;
ll z[MAXN], a[MAXN], b[MAXN];

ll calculate_power(ll x) {
    ll total_power = 0;
    for (int i = 0; i < n; i++) {
        if (x <= z[i]) {
            total_power += a[i] * x;
        } else {
            total_power += a[i] * z[i] + b[i] * (x - z[i]);
        }
    }
    return total_power;
}

int main() {
    scanf("%d %lld", &n, &p);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &z[i], &a[i], &b[i]);
    }

    ll low = 1, high = MAXP, mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (calculate_power(mid) >= p) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    printf("%lld\n", low);
    return 0;
}