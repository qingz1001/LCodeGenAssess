#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 2000
#define MAX_P 100000

typedef long long ll;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

int main() {
    int test, m;
    scanf("%d", &test);

    while (test--) {
        scanf("%d", &m);

        ll result = 1;
        for (int i = 0; i < m; i++) {
            ll p, q;
            scanf("%lld %lld", &p, &q);

            ll phi_cycle = p - 1;
            for (int j = 2; j <= q; j++) {
                phi_cycle = phi_cycle * p / gcd(phi_cycle, p);
            }

            result = lcm(result, phi_cycle);
        }

        printf("%lld\n", result);
    }

    return 0;
}