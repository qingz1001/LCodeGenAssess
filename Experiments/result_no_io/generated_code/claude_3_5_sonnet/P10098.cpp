#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef long long ll;

typedef struct {
    int z, a, b;
} Engine;

int n;
ll p;
Engine engines[MAX_N];

ll calc_power(ll x) {
    ll total_power = 0;
    for (int i = 0; i < n; i++) {
        if (x <= engines[i].z) {
            total_power += (ll)engines[i].a * x;
        } else {
            total_power += (ll)engines[i].a * engines[i].z + (ll)engines[i].b * (x - engines[i].z);
        }
    }
    return total_power;
}

ll binary_search() {
    ll left = 1, right = 1e12;
    while (left < right) {
        ll mid = left + (right - left) / 2;
        if (calc_power(mid) >= p) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %lld", &n, &p);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &engines[i].z, &engines[i].a, &engines[i].b);
    }
    
    ll result = binary_search();
    printf("%lld\n", result);
    
    return 0;
}