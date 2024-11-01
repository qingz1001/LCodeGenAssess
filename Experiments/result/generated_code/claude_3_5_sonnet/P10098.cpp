#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef long long ll;

typedef struct {
    ll z, a, b;
} Engine;

int n;
ll p;
Engine engines[MAX_N];

ll calculate_power(ll voltage) {
    ll total_power = 0;
    for (int i = 0; i < n; i++) {
        if (voltage <= engines[i].z) {
            total_power += engines[i].a * voltage;
        } else {
            total_power += engines[i].a * engines[i].z + engines[i].b * (voltage - engines[i].z);
        }
    }
    return total_power;
}

ll binary_search() {
    ll left = 1, right = 1e12;
    while (left < right) {
        ll mid = left + (right - left) / 2;
        if (calculate_power(mid) >= p) {
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
        scanf("%lld %lld %lld", &engines[i].z, &engines[i].a, &engines[i].b);
    }

    ll result = binary_search();
    printf("%lld\n", result);

    return 0;
}