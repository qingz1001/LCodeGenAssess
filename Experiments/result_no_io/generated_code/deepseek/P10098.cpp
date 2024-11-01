#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_P 1000000000000LL

typedef long long ll;

int n;
ll p;
ll z[MAX_N], a[MAX_N], b[MAX_N];

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

ll binary_search_voltage() {
    ll low = 1, high = MAX_P, mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (calculate_power(mid) >= p) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int main() {
    scanf("%d %lld", &n, &p);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &z[i], &a[i], &b[i]);
    }
    printf("%lld\n", binary_search_voltage());
    return 0;
}